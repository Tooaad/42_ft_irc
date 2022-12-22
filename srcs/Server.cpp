/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:43:29 by gpernas-          #+#    #+#             */
/*   Updated: 2022/12/22 22:01:50 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void	saveArgs(std::string *args, int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        args[i - 1] = argv[i];
    // 	std::cout << args[i - 1];
	}
}

void createNetwork(std::string *args) {
    (void)args;
    
}

void connectNetwork(std::string *args) {
    (void)args;
}

int main(int argc, char **argv) {
    std::string*	args = NULL;
    saveArgs(args, argc, argv);
	
    if (argc == 2)
        createNetwork(args);
    else if (argc == 4)
        connectNetwork(args);
    return 0;





    
}