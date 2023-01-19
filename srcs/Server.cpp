/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:43:29 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/19 10:50:47 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

IRC::Server::Server() {
}

IRC::Server::~Server() {
}


int IRC::Server::getSocket(void) const {
   return this->sSocket; 
}



void IRC::Server::connectNetwork(std::string *args) {
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
