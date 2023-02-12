/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 23:10:27 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/12 19:35:31 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Privmsg.hpp"


IRC::PrivMsg::PrivMsg() {}
IRC::PrivMsg::~PrivMsg() {}

void	IRC::PrivMsg::exec(IRC::Server *server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, *server, user, 0);
	
	if (this->args.size() == 0)
		return setError(ERR_NORECIPTIENT, *server, user, 1, this->command.c_str());

	std::vector<std::string> argSplit = splitString(this->args, " ", 1);
	if (argSplit[1].size() == 0)
		return setError(ERR_NOTEXTTOSEND, *server, user, 0);
	
	if (argSplit[0].at(0) == '#')
	{
		std::vector<IRC::Channel>::iterator receptor = server->getChannelIt(argSplit[0]);
		if (receptor.base() == NULL)
			return setError(ERR_NOSUCHCHANNEL, *server, user, 1, argSplit[0].c_str());

		// TODO: REVISAR CONDICION
		if((!user.isInChannel(*receptor) && !receptor->isPublicMsg()) && (receptor->isModerated() && !receptor->isOperator(user) && !receptor->isModerator(user)))
			return setError(ERR_CANNOTSENDTOCHAN, *server, user, 1, argSplit[1].c_str());

		receptor->sendMessageToUsers(user, ":" + user.getNick() + " PRIVMSG " + argSplit[0] + " " + argSplit[1] + "\n");
	}
	else
	{
		std::vector<IRC::User>::iterator receptor = findUser(server->getUsers(), argSplit[0]);
		
		if (receptor == server->getUsers().end())
			return setError(ERR_NOSUCHNICK, *server, user, 1, argSplit[0].c_str());
	
		argSplit[1] = ":" + user.getNick() + " PRIVMSG " + receptor->getNick() + " " + argSplit[1] + "\n";
		receptor->sendMessage(argSplit[1]);
	}
}
