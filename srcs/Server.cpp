/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:43:29 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/18 13:43:35 by gpernas-         ###   ########.fr       */
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

    // Mark the Sock to sSocket in
    listen(sSocket, SOMAXCONN);
    return 0; 
}


int main(int argc, char **argv) {
    std::string	args[argc - 1];
    saveArgs(args, argc, argv);
    
    IRC::Server server;
    if (argc == 3)
        server.createNetwork(args);
    else if (argc == 4)
        connectNetwork(args);
	
    IRC::Client client(server.getSocket());
    client.clientSetup();
    
    // Close sSocket
    close(server.getSocket());
    
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

    // While receiving- display msg, echo msg
    
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

    close(server.getSocket());
    return 0;
}