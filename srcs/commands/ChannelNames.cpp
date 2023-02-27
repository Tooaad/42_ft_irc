/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelNames.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:10:20 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/27 20:43:07 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelNames.hpp"


IRC::ChannelNames::ChannelNames() {}
IRC::ChannelNames::~ChannelNames() {}

void	IRC::ChannelNames::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, *server, user, 0);
	
	std::vector<std::string> argsArray = splitString(args, " ");
	std::vector<std::string> channelsArrayStr = splitString(argsArray[0], ",");
	std::vector<Channel> channelsArray;
	
	std::vector<Channel>::iterator channelIt;
	for (std::vector<std::string>::iterator it = channelsArrayStr.begin(); it != channelsArrayStr.end(); it++)
	{
		if (it->size() == 0)
			continue ;
		channelIt = server->findChannel(*it);
		if (channelIt == server->getChannels().end())
			channelsArray.push_back(Channel(*it));
		else
			channelsArray.push_back(*channelIt);
	}
	
	if (channelsArray.size() > 0)
		printNames(*server, user, channelsArray.begin(), channelsArray.end());
	else
		setReply(RPL_ENDOFNAMES, *server, user, 1, "*");
}

void	IRC::ChannelNames::printNames(IRC::Server server, IRC::User user, std::vector<IRC::Channel>::iterator itBegin, std::vector<IRC::Channel>::iterator itEnd)
{
	for (std::vector<Channel>::iterator it = itBegin; it != itEnd; ++it)
	{
		if (it->isSecret() && !user.isInChannel(*it))
			continue ;

		if (it->getUsers().size() > 0)
			setReply(RPL_NAMREPLY, server, user, 2, it->getName().c_str(), it->getUsersString().c_str());

		setReply(RPL_ENDOFNAMES, server, user, 1, it->getName().c_str());
	}
}
