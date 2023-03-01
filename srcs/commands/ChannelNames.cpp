/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelNames.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:10:20 by karisti-          #+#    #+#             */
/*   Updated: 2023/03/01 11:24:49 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelNames.hpp"


IRC::ChannelNames::ChannelNames() {}
IRC::ChannelNames::~ChannelNames() {}

void	IRC::ChannelNames::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setReply(ERR_NOTREGISTERED, *server, user, 0);
	
	std::vector<std::string> argsArray = splitString(args, " ");
	if (argsArray.size() == 0)
		return ;
	
	std::vector<std::string> channelsArrayStr = splitString(argsArray[0], ",");
	for (std::vector<std::string>::iterator it = channelsArrayStr.begin(); it != channelsArrayStr.end(); it++)
	{
		if (it->size() == 0)
			continue ;
		
		std::map<std::string, IRC::Channel>::iterator channelIt = server->findChannel(*it);
		if (channelIt != server->getChannels().end())
		{
			if (!channelIt->second.isSecret() || user.isInChannel(channelIt->second))
				setReply(RPL_NAMREPLY, *server, user, 2, channelIt->second.getName().c_str(), channelIt->second.getUsersString().c_str());
		}
		setReply(RPL_ENDOFNAMES, *server, user, 1, it->c_str());
	}
}
