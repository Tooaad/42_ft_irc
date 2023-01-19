/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:43:29 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/19 11:45:14 by karisti-         ###   ########.fr       */
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
	if ((this->sSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Error opening socket");
		return -1;
	}
	
	// Bind the Socket to any free IP / Port
	sockaddr_in hint;
	hint.sin_family = AF_INET;                          // IPv4 type
	// hint.sin_addr.s_addr = INADDR_ANY;
	hint.sin_port = htons(atoi(args[0].c_str()));       // Little Endian (for bigger numbers) | Host To Network Short
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
	
	
	if (bind(sSocket, (struct sockaddr *)&hint, sizeof(hint)) < 0)
	{
		perror("Error binding socket");
		return -1;
	}

	if (fcntl(sSocket, F_SETFL, O_NONBLOCK) < 0) {
		perror("Error making server socket non blocking");
		return -1;
	}

	listen(sSocket, SOMAXCONN);
	
	
	kq = kqueue();
	
	EV_SET(change_event, sSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);

	if (kevent(kq, change_event, 1, NULL, 0, NULL) == -1)
	{
		perror("kevent");
		return -1;
	}
	 
	return 0;
}

int	IRC::Server::getKq(void) {
	return this->kq;
}

struct kevent*	IRC::Server::getEvent(void) {
	return &this->event[0];
}

struct kevent*	IRC::Server::getChangeEvent(void) {
	return &this->change_event[0];
}
