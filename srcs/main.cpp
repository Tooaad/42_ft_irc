/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:45:50 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/19 11:57:01 by karisti-         ###   ########.fr       */
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
	
	// Server loop
	while (true) {
		if ((new_events = kevent(server.getKq(), NULL, 0, server.getEvent(), 1, NULL)) == -1) {
			perror("kevent");
			return -1;
		}

		// kqueue events loop
		for (int i = 0; i < new_events; i++) {
			int event_fd = server.getEvent()[i].ident;

			// Client disconnected
			if (server.getEvent()[i].flags & EV_EOF) {
				std::cout << "Client has disconnected" << std::endl;
				close(event_fd);
			}
			// New client connected
			else if (event_fd == server.getSocket()) {
				IRC::Client client(server.getSocket());
				client.clientSetup();

				EV_SET(server.getChangeEvent(), client.getSocket(), EVFILT_READ, EV_ADD, 0, 0, NULL);
				if (kevent(server.getKq(), server.getChangeEvent(), 1, NULL, 0, NULL) < 0)
				{
					perror("kevent error");
					return -1;
				}
			}
			// New message from client
			else if (server.getEvent()[i].filter & EVFILT_READ) {
				char buf[4096];
				int bytesRec;

				memset(buf, 0, 4096);
				if (fcntl(event_fd, F_SETFL, O_NONBLOCK) < 0) {
					perror("Error making client socket non blocking");
					return -1;
				}
				
				if ((bytesRec = recv(event_fd, buf, 4096, 0)) == -1) {
					std::cout << "Error in recv(). Quitting" << std::endl;
					return -1;
				}

				// Todo: Comprobar si ocurre alguna vez para borrar sino
				if (bytesRec == 0) {
					std::cout << "Client disconnected " << std::endl;
					return -1;
				}
				// ***********

				std::cout << "Msg: " << std::string(buf, 0, bytesRec) << std::endl;

				send(event_fd, buf, bytesRec + 1, 0);
			}
		}
	}

	close(server.getSocket());
	return 0;
}
