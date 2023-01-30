/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 23:10:27 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/30 10:59:45 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Privmsg.hpp"

IRC::PrivMsg::PrivMsg()
{	
}

IRC::PrivMsg::~PrivMsg()
{	
}

void IRC::PrivMsg::exec(IRC::Server *server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, 0);
	
	if (this->args.size() == 0)
		return setError(ERR_NORECIPTIENT, 1, this->command.c_str());

	std::vector<std::string> argSplit = splitString(this->args, " ", 1);
	
	if (argSplit[1].size() == 0)
		return setError(ERR_NOTEXTTOSEND, 0);
	
	IRC::User& receptor = *findUser(server->getUsers(), argSplit[0]);
	// Mirar argSplit[0] es un canal y si existe
	
	
	if (receptor == NULL)
		return setError(ERR_NOSUCHCHANNEL, 1, argSplit[0].c_str());
		
	
	send(receptor.getSocket(), argSplit[1].c_str(), argSplit[1].size(), 0);
	
	// if (usuario/canal is in find(arraycanal))
		// return setError(ERR_CANNOTSENDTOCHAN, 1, argSplit[1]);
}