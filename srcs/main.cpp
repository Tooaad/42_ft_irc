/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:45:50 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/20 14:29:19 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Client.hpp"
#include "../includes/utils.hpp"

void saveArgs(std::string *args, int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		args[i - 1] = argv[i];
	}
}

int main(int argc, char **argv)
{
	std::string args[argc - 1];
	saveArgs(args, argc, argv);

	// split_string(" hola  buenas tardes q ");


	IRC::Server server(args[1]);
	if (argc == 3)
		server.createNetwork(args);
	else if (argc == 4)
		server.connectNetwork(args);

	server.loop();
	close(server.getSocket()); // TODO: Mirar como cerrar bien, tras Ctrl+C no llega aqui
	return 0;
}
