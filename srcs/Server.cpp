/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:43:29 by gpernas-          #+#    #+#             */
/*   Updated: 2022/12/27 23:11:15 by gpernas-         ###   ########.fr       */
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
    int listening = socket(AF_INET, SOCK_STREAM, 0);

    
    if (argc == 2)
        createNetwork(args);
    else if (argc == 4)
        connectNetwork(args);
    return 0;





    
}