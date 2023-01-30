/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 23:10:27 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/30 18:00:57 by gpernas-         ###   ########.fr       */
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
	
	if (argSplit[0].at(0) == '#')
	{
		std::vector<IRC::Channel>::iterator receptor = server->getChannelIt(argSplit[0]);
		if (receptor.base() == NULL)
			return setError(ERR_NOSUCHCHANNEL, 1, argSplit[0].c_str());
			
		if(!receptor->existsUser(user))
			return setError(ERR_CANNOTSENDTOCHAN, 1, argSplit[1].c_str());
				
		receptor->sendMessage(argSplit[1] + "\n");
	}
	else
	{
		IRC::User receptor = findUser(server->getUsers(), argSplit[0]);	
		if (receptor == NULL)
			return setError(ERR_NOSUCHNICK, 1, argSplit[0].c_str());
	
		argSplit[1] += "\n";
		send(receptor.getSocket(), argSplit[1].c_str(), argSplit[1].size(), 0);
	}
	
}