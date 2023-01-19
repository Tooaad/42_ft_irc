/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:45:50 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/19 10:50:36 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Client.hpp"

void saveArgs(std::string *args, int argc, char **argv) {
	for (int i = 1; i < argc; i++) {
		args[i - 1] = argv[i];
	}
}

int main(int argc, char **argv) {
	std::string	args[argc - 1];
	saveArgs(args, argc, argv);
	
	IRC::Server server;
	if (argc == 3)
		server.createNetwork(args);
	else if (argc == 4)
		server.connectNetwork(args);

	int new_events;
	
	while (true)
	{
		// Check for new events, but do not register new events with
		// the kqueue. Hence the 2nd and 3rd arguments are NULL, 0.
		// Only handle 1 new event per iteration in the loop; 5th
		// argument is 1.

		
		new_events = kevent(server.getKq(), NULL, 0, server.getEvent(), 1, NULL);
		if (new_events == -1) {
			perror("kevent");
			exit(1);
		}

		for (int i = 0; i < new_events; i++) {
			int event_fd = server.getEvent()[i].ident;

			// When the client disconnects an EOF is sent. By closing the file
			// descriptor the event is automatically removed from the kqueue.
			if (server.getEvent()[i].flags & EV_EOF)
			{
				printf("Client has disconnected");
				close(event_fd);
			}
			// If the new event's file descriptor is the same as the listening
			// socket's file descriptor, we are sure that a new client wants 
			// to connect to our socket.
			else if (event_fd == server.getSocket())
			{
				// Incoming socket connection on the listening socket.
				// Create a new socket for the actual connection to client.

				IRC::Client client(server.getSocket());
				client.clientSetup();

				// Put this new socket connection also as a 'filter' event
				// to watch in kqueue, so we can now watch for events on this
				// new socket.
				EV_SET(server.getChgEvent(), client.getSocket(), EVFILT_READ, EV_ADD, 0, 0, NULL);
				if (kevent(server.getKq(), server.getChgEvent(), 1, NULL, 0, NULL) < 0)
				{
					perror("kevent error");
				}
			}
			else if (server.getEvent()[i].filter & EVFILT_READ)
			{
				// Read bytes from socket
				char buf[4096];

				if(fcntl(event_fd, F_SETFL, O_NONBLOCK) < 0) {
					// handle error
				}
				// Clear the buffer
				memset(buf, 0, 4096);
				// Wait for msg
				int bytesRec = recv(event_fd, buf, 4096, 0);
				
				if (bytesRec == -1)
				{
					std::cout << "Error in recv(). Quitting" << std::endl;
					break;
				}
		
				if (bytesRec == 0)
				{
					std::cout << "Client disconnected " << std::endl;
					break;
				}

				std::cout << "Msg: " << std::string(buf, 0, bytesRec) << std::endl;

				send(event_fd, buf, bytesRec + 1, 0); // +1 Last \0
			}
		}
	}

	close(server.getSocket());
	return 0;
}
