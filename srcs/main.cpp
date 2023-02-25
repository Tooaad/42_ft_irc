/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:45:50 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/25 11:30:27 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/utils.hpp"


void saveArgs(std::string *args, int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
		args[i - 1] = argv[i];
}

void cleaks(void)
{
	system("leaks ircserv");
}

int main(int argc, char **argv)
{
	// if (argc != 3 || argc != 4)
	// {
	// 	std::cout << "error bad arguments" << std::endl;
	// 	return -1;
	// }
	
	atexit(cleaks);
	
	std::string args[argc - 1];
	saveArgs(args, argc, argv);

	IRC::Server server(args[1]);
	if (argc == 3)
		server.createNetwork(args);
	else if (argc == 4)
		server.connectNetwork(args);

	server.loop();
	server.terminateServer();

	return 0;
}
