/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelTopic.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:29:29 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/28 14:44:41 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelTopic.hpp"


IRC::ChannelTopic::ChannelTopic() {}
IRC::ChannelTopic::~ChannelTopic() {}

void	IRC::ChannelTopic::exec(IRC::Server* server, IRC::User& user)
{
	/** CHECK ALL POSSIBLE ERRORS **/
	if (!user.isAuthenticated())
		return setReply(ERR_NOTREGISTERED, *server, user, 0);
	
	std::vector<std::string> argsArray = splitString(args, " ", 1);
	if (argsArray.size() < 1 || argsArray[0].size() == 0)
		return setReply(ERR_NEEDMOREPARAMS, *server, user, 1, this->command.c_str());
		
	std::vector<IRC::Channel>::iterator channel = server->findChannel(argsArray[0]);
	if (channel == server->getChannels().end())
		return setReply(ERR_NOSUCHCHANNEL, *server, user, 1, argsArray[0].c_str());

	if(!channel->existsUser(user))
		return setReply(ERR_NOTONCHANNEL, *server, user, 1, argsArray[1].c_str());
	
	if (argsArray.size() == 1)
	{
		/** SEND TOPIC IN REPLY **/
		if (channel->getTopic().size() == 0)
			setReply(RPL_NOTOPIC, *server, user, 1, channel->getName().c_str());
		else
			setReply(RPL_TOPIC, *server, user, 2, channel->getName().c_str(), channel->getTopic().c_str());
	}
	else
	{
		/** CHECK PERMISSIONS, CHANGE TOPIC AND SEND IN REPLY **/
		if (!channel->isFreeTopic() && !channel->isOperator(user))
			return setReply(ERR_CHANOPRIVSNEEDED, *server, user, 1, argsArray[1].c_str());
		
		channel->setTopic(argsArray[1]);
		setActionInReply(*server, user, *channel, "TOPIC " + channel->getName() + " " + channel->getTopic());
	}
}
