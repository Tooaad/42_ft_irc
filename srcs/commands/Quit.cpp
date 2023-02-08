/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:46:20 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/08 11:01:32 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Quit.hpp"


IRC::Quit::Quit() {}
IRC::Quit::~Quit() {}

void	IRC::Quit::exec(IRC::Server* server, IRC::User& user)
{
	std::string message;
	
	if (args.size() > 0)
		message = "Quit: " + args;
	else
		message = "Client exited";
		
	server->closeClient(user, message);
}


/*
TODO: solo se muestra 1
:karist!kiwiirccom@1Sb.j18.j49ElA.virtual QUIT :Client exited
:Guest1378!kiwiirccom@1Sb.j18.j49ElA.virtual QUIT :Quit: me voy
:Guest138!kiwiirccom@1Sb.j18.j49ElA.virtual QUIT :Quit: Connection closed
*/
