/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelTopic.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:29:29 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/06 18:19:05 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelTopic.hpp"

IRC::ChannelTopic::ChannelTopic() {}
IRC::ChannelTopic::~ChannelTopic() {}

void IRC::ChannelTopic::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, 0);
	
	std::vector<std::string> argsArray = splitString(args, " ", 1);
	
	if (argsArray.size() < 1 || argsArray[0].size() == 0)
		return setError(ERR_NEEDMOREPARAMS, 1, this->command.c_str());
		
	std::vector<IRC::Channel>::iterator channel = server->getChannelIt(argsArray[0]);
	if (argsArray.size() == 1)
	{
		if (channel->getTopic().size() == 0)
			setReply(RPL_NOTOPIC, user, 1, channel->getName().c_str());
		else
			setReply(RPL_TOPIC, user, 2, channel->getName().c_str(), channel->getTopic().c_str());
	}
	else
	{
		if(!channel->existsUser(user))
			return setError(ERR_NOTONCHANNEL, 1, argsArray[1].c_str());
			
		if (!channel->isFreeTopic() && !channel->isOperator(user))
			return setError(ERR_CHANOPRIVSNEEDED, 1, argsArray[1].c_str());
		
		channel->setTopic(argsArray[1]);
	}

}
