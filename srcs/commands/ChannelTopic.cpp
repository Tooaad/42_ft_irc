/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelTopic.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:29:29 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/23 18:45:31 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelTopic.hpp"


IRC::ChannelTopic::ChannelTopic() {}
IRC::ChannelTopic::~ChannelTopic() {}

void	IRC::ChannelTopic::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, *server, user, 0);
	
	std::vector<std::string> argsArray = splitString(args, " ", 1);
	
	if (argsArray.size() < 1 || argsArray[0].size() == 0 || argsArray[1].size() == 0)
		return setError(ERR_NEEDMOREPARAMS, *server, user, 1, this->command.c_str());
		
	std::vector<IRC::Channel>::iterator channel = server->getChannelIt(argsArray[0]);
	if (argsArray.size() == 1)
	{
		if (channel->getTopic().size() == 0)
			setReply(RPL_NOTOPIC, *server, user, 1, channel->getName().c_str());
		else
			setReply(RPL_TOPIC, *server, user, 2, channel->getName().c_str(), channel->getTopic().c_str());
	}
	else
	{
		if(!channel->existsUser(user))
			return setError(ERR_NOTONCHANNEL, *server, user, 1, argsArray[1].c_str());
			
		if (!channel->isFreeTopic() && !channel->isOperator(user))
			return setError(ERR_CHANOPRIVSNEEDED, *server, user, 1, argsArray[1].c_str());
		
		channel->setTopic(argsArray[1]);
		
		setActionInReply(*server, user, *channel, "TOPIC " + channel->getName() + " " + channel->getTopic());
	}
}

// :karisti!kepa@Mv6.j18.j49ElA.virtual TOPIC #prueba :Bienvenido al canal
// :totoadd!Tototoadd1@c1r14s4.42madrid.com TOPIC #test::test1
