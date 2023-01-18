/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:43:29 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/18 19:54:02 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Client.hpp"

IRC::Server::Server() {
}

IRC::Server::~Server() {
}


int IRC::Server::getSocket(void) const {
   return this->sSocket; 
}

void saveArgs(std::string *args, int argc, char **argv) {
	for (int i = 1; i < argc; i++) {
		args[i - 1] = argv[i];
	}
}

void connectNetwork(std::string *args) {
	(void)args;
}

int IRC::Server::createNetwork(std::string *args) {
	(void) args;
	this->sSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (sSocket == -1)
	{
		std::cerr << "Cannot create a Socket" << std::endl;
		return -1;
	}
	
	// Bind the Socket to any free IP / Port
	sockaddr_in hint;
	hint.sin_family = AF_INET;                          // IPv4 type
	hint.sin_port = htons(atoi(args[0].c_str()));       // Little Endian (for bigger numbers) | Host To Network Short
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
	
	bind(sSocket, (struct sockaddr *)&hint, sizeof(hint));


	if(fcntl(sSocket, F_SETFL, O_NONBLOCK) < 0) {
		// handle error
	}

	
	// Mark the Sock to sSocket in
	listen(sSocket, SOMAXCONN);
	
	

	// Prepare the kqueue.
	kq = kqueue();
	
	 // Create event 'filter', these are the events we want to monitor.
	// Here we want to monitor: socket_listen_fd, for the events: EVFILT_READ 
	// (when there is data to be read on the socket), and perform the following
	// actions on this kevent: EV_ADD and EV_ENABLE (add the event to the kqueue 
	// and enable it).
	
	EV_SET(change_event, sSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);

	// Register kevent with the kqueue.
	if (kevent(kq, change_event, 1, NULL, 0, NULL) == -1)
	{
		perror("kevent");
		exit(1);
	}
	 
	return 0;
}

int	IRC::Server::getKq(void) {
	return this->kq;
}

struct kevent*	IRC::Server::getEvent(void) {
	return &this->event[0];
}

struct kevent*	IRC::Server::getChgEvent(void) {
	return &this->change_event[0];
}

int main(int argc, char **argv) {
	std::string	args[argc - 1];
	saveArgs(args, argc, argv);
	
	IRC::Server server;
	if (argc == 3)
		server.createNetwork(args);
	else if (argc == 4)
		connectNetwork(args);
	
	// Close sSocket
	//close(server.getSocket());
	
	// AF_INET ->       IPv4
	// SOCK_STREAM ->   TCP con
	
	// -------------------------------------------------
	// Creating a Socket
	// int sSocket = socket(AF_INET, SOCK_STREAM, 0);
	// if (sSocket == -1)
	// {
	//     std::cerr << "Cannot create a Socket" << std::endl;
	//     return -1;
	// }

	// // Bind the Socket to any free IP / Port
	// sockaddr_in hint;
	// hint.sin_family = AF_INET;          // IPv4 type
	// hint.sin_port = htons(54000);      // Little Endian (for bigger numbers) | Host To Network Short
	// inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
	
	// bind(sSocket, (struct sockaddr *)&hint, sizeof(hint));


	// // Mark the Sock to sSocket in
	// listen(sSocket, SOMAXCONN);

	// // Accept a Call
	// sockaddr_in client;
	// socklen_t clientSize = sizeof(client);
	

	// ///fcntl
	// int clientSocket = accept(sSocket, (struct sockaddr *)&client, &clientSize);
	 
	// char host[NI_MAXHOST];
	// char service[NI_MAXSERV];
	// memset(host, 0, NI_MAXHOST);
	// memset(service, 0, NI_MAXSERV);
	
	// if (getnameinfo((struct sockaddr *) &client, sizeof(clientSize), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	//     std::cout << "Host: " << host << "connected on port" << service << std::endl;
	// else 
	// {
	//     inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
	//     std::cout << "Host: " << host << "connected on port" << ntohs(client.sin_port) << std::endl;
	// }

	// // Close sSocket
	// close(sSocket);

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
	







	// While receiving- display msg, echo msg
	/*
	char buf[4096];
	while (true)
	{  
		// Clear the buffer
		memset(buf, 0, 4096);
		// Wait for msg
		int bytesRec = recv(client.getSocket(), buf, 4096, 0);
		
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

		send(client.getSocket(), buf, bytesRec + 1, 0); // +1 Last \0

	}
	*/
	close(server.getSocket());
	return 0;
}

/*
std::cout << "FD: " << clientSocket << std::endl;
fcntl(clientSocket, F_SETFL, O_NONBLOCK);
std::cout << "FD: " << clientSocket << std::endl;

if ((fcntl(clientSocket, F_GETFL) & O_NONBLOCK))
	std::cout << "O_NONBLOCK set" << std::endl;
else
	std::cout << "not O_NONBLOCK" << std::endl;
*/
