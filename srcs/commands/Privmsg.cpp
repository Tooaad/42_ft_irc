/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 23:10:27 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/28 14:44:41 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Privmsg.hpp"


IRC::PrivMsg::PrivMsg() {}
IRC::PrivMsg::~PrivMsg() {}

void	IRC::PrivMsg::exec(IRC::Server *server, IRC::User& user)
{
	/** CHECK POSSIBLE ERRORS **/
	if (!user.isAuthenticated())
		return setReply(ERR_NOTREGISTERED, *server, user, 0);
	
	if (this->args.size() == 0)
		return setReply(ERR_NORECIPTIENT, *server, user, 1, this->command.c_str());

	std::vector<std::string> argSplit = splitString(this->args, " ", 1);
	if (argSplit.size() <= 1 || argSplit[1].size() == 0)
		return setReply(ERR_NOTEXTTOSEND, *server, user, 0);
	
	if (argSplit[0].at(0) == '#')
	{
		/** MESSAGE TO CHANNEL **/
		std::vector<IRC::Channel>::iterator receptor = server->findChannel(argSplit[0]);
		if (receptor == server->getChannels().end())
			return setReply(ERR_NOSUCHCHANNEL, *server, user, 1, argSplit[0].c_str());

		if (receptor->isModerated() && (!receptor->isOperator(user) && !receptor->isModerator(user)))
			return setReply(ERR_CANNOTSENDTOCHAN, *server, user, 1, argSplit[1].c_str());

		if((!user.isInChannel(*receptor) && !receptor->isPublicMsg()))
			return setReply(ERR_CANNOTSENDTOCHAN, *server, user, 1, argSplit[1].c_str());

		receptor->sendMessageToUsers(user, ":" + user.getNick() + " " + this->command + " " + argSplit[0] + " " + argSplit[1]);
	}
	else
	{
		/** PRIVATE MESSAGE **/
		std::vector<IRC::User>::iterator receptor = findUser(server->getUsers(), argSplit[0]);
		if (receptor == server->getUsers().end())
			return setReply(ERR_NOSUCHNICK, *server, user, 1, argSplit[0].c_str());
		
		argSplit[1] = ":" + user.getNick() + " " + this->command + " " + receptor->getNick() + " " + argSplit[1];
		receptor->sendMessage(argSplit[1]);
	}
}
