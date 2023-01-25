/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:45:50 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/25 12:31:19 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Client.hpp"
#include "../includes/utils.hpp"

void saveArgs(std::string *args, int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
		args[i - 1] = argv[i];
}

int main(int argc, char **argv)
{
	// if (argc != 3 || argc != 4)
	// {
	// 	std::cout << "error bad arguments" << std::endl;
	// 	return -1;
	// }
	
	std::string args[argc - 1];
	saveArgs(args, argc, argv);

	IRC::Server server(args[1]);
	if (argc == 3)
		server.createNetwork(args);
	else if (argc == 4)
		server.connectNetwork(args);

	server.loop();
	close(server.getSocket()); // TODO: Mirar como cerrar bien, tras Ctrl+C no llega aqui
	return 0;
}
