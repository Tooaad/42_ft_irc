/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:03:43 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/22 11:34:24 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"


IRC::Client::Client() {}

IRC::Client::Client(int serverSocket)
{
	this->size = sizeof(this->address);
	this->cSocket = accept(serverSocket, (struct sockaddr *)&this->address, &this->size);

	if (this->cSocket == -1)
		perror("Accept socket error");
}

IRC::Client::Client(const IRC::Client &other) { *this = other; }
IRC::Client::~Client() {}

IRC::Client &IRC::Client::operator=(const IRC::Client &other)
{
	if (this != &other)
	{
		this->address = other.address;
		this->cSocket = other.cSocket;
		this->size = other.size;
		this->hostname = other.hostname;
		
	}
	
	return *this;
}

/* -- Getters -- */
sockaddr_in		IRC::Client::getAddress(void) const { return this->address; }
int				IRC::Client::getSocket(void) const { return this->cSocket; }
socklen_t		IRC::Client::getSize(void) const { return this->size; }
char			*IRC::Client::getHostname(void) const { return this->hostname; }

void			IRC::Client::setHostname(char *hostname) { this->hostname = hostname; }

/* -- Member functions -- */
void	IRC::Client::setup(void)
{
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);
	
	if (getnameinfo((struct sockaddr *) &this->address, sizeof(this->size), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		std::cout << "Host1: " << host << " connected on port " << service << std::endl;
	else 
	{
		inet_ntop(AF_INET, &this->address.sin_addr, host, NI_MAXHOST);
		std::cout << "Host: " << host << " connected on port " << ntohs(this->address.sin_port) << std::endl;
	}
	this->setHostname(host);
}
