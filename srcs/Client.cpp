/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:03:43 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/18 13:24:44 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

IRC::Client::Client(int sSocket) {
    this->size = sizeof(this->address);
    this->cSocket = accept(sSocket, (struct sockaddr *)&this->address, &this->size);
}

IRC::Client::~Client() {
}

void IRC::Client::clientSetup() const {
    // Accept a Call
     
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
}

sockaddr_in IRC::Client::getClientAddress() const {
	return this->address;
}

socklen_t IRC::Client::getClientSize() const {
	return this->size;	
}

int IRC::Client::getSocket() const {
	return this->cSocket;	
}
