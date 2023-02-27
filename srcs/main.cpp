/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:45:50 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/27 18:36:17 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/utils.hpp"


void saveArgs(std::string *args, int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
		args[i - 1] = argv[i];
}

int		checkArgs(std::string *args, int argc)
{
	int	serverPort = atoi(args[0].c_str());
	
	if (argc != 3)
	{
		std::cout << "./ircserv <PORT> <SEVER_PASS>" << std::endl;
		return 1;
	}
	
	if (serverPort < 0 || serverPort > 65535)
	{
		std::cout << "Server port must be between 0 and 65535" << std::endl;
		return 1;
	}
	
	return 0;
}



void cleaks(void)
{
	system("leaks ircserv");
}

int main(int argc, char **argv)
{
	atexit(cleaks);
	
	std::string args[argc - 1];
	saveArgs(args, argc, argv);

	if (checkArgs(args, argc))
		return 0;

	IRC::Server server(args[1]);
	if (argc != 3)
	{
		std::cout << "./ircserv <PORT> <SEVER_PASS>" << std::endl;
		return 1;
	}

	server.createNetwork(args);
	server.loop();
	server.terminateServer();

	return 0;
}
