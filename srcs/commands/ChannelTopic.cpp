/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelTopic.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:29:29 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/30 19:24:28 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelTopic.hpp"

IRC::ChannelTopic::ChannelTopic()
{
}

IRC::ChannelTopic::~ChannelTopic()
{
}

void IRC::ChannelTopic::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, 0);
	
	std::vector<std::string> argsArray = splitString(args, " ");
	
	if (argsArray.size() < 1 || argsArray[0].size() == 0)
		return setError(ERR_NEEDMOREPARAMS, 1, this->command.c_str());
		
	std::vector<IRC::Channel>::iterator channel = server->getChannelIt(argsArray[0]);
	if (argsArray.size() == 1)
	{
		//RPL_TOPIC - send(user.getSocket(), channel->getTopic().c_str(), channel->getTopic().size(), 0);
		//RPL_NOTOPIC
		// 
	}
	else
	{	
		if(!channel->existsUser(user))
			return setError(ERR_NOTONCHANNEL, 1, argsArray[1].c_str());
			
		// if (not operator)
			// return setError(ERR_CHANOPRIVSNEEDED, 1, argsArray[1].c_str());
		
		channel->setTopic(argsArray[1]);
	}

}