/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:43:29 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/09 12:18:21 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void	saveArgs(std::string *args, int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        args[i - 1] = argv[i];
	}
}

void createNetwork(std::string *args) {
    (void)args;
    
}

void connectNetwork(std::string *args) {
    (void)args;
}

int main(int argc, char **argv) {
    std::string	args[argc - 1];
    saveArgs(args, argc, argv);
	
    // AF_INET ->       IPv4
    // SOCK_STREAM ->   TCP con
    
    // -------------------------------------------------
    // Creating a Socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        std::cerr << "Cannot create a Socket" << std::endl;
        return -1;
    }

    // Bind the Socket to any free IP / Port
    sockaddr_in hint;
    hint.sin_family = AF_INET;  // IPv4 type
    hint.sin_port = htons(54000);      // Little Endian (for bigger numbers) | Host To Network Short
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    
    bind(listening, (struct sockaddr *)&hint, sizeof(hint));


    // Mark the Sock to listening in
    listen(listening, SOMAXCONN);

    // Accept a Call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    
    int clientSocket = accept(listening, (struct sockaddr *)&client, &clientSize);
     
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
    
    if (getnameinfo((struct sockaddr *) &client, sizeof(clientSize), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
        std::cout << "Host: " << host << "connected on port" << service << std::endl;
    else 
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << "Host: " << host << "connected on port" << ntohs(client.sin_port) << std::endl;
    }

    // Close Listening
    close(listening);

    // While receiving- display msg, echo msg
    char buf[4096];
    while (true)
    {  
        // Clear the buffer
        memset(buf, 0, 4096);
        // Wait for msg
        int bytesRec = recv(clientSocket, buf, 4096, 0);
        
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

        send(clientSocket, buf, bytesRec + 1, 0); // +1 Last \0

    }

    close(listening);

    if (argc == 2)
        createNetwork(args);
    else if (argc == 4)
        connectNetwork(args);
    return 0;





    
}