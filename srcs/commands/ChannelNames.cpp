/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelNames.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:10:20 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/06 19:46:04 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelNames.hpp"

IRC::ChannelNames::ChannelNames() {}
IRC::ChannelNames::ChannelNames(const IRC::ChannelNames &other) { *this = other; }
IRC::ChannelNames::~ChannelNames() {}

IRC::ChannelNames &IRC::ChannelNames::operator=(const IRC::ChannelNames &other)
{
	if (this != &other)
		channelsArray = other.channelsArray;
	return *this;
}

void IRC::ChannelNames::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, 0);
	
	parseArgs(server);
	
	if (this->channelsArray.size() > 0)
		printNames(*server, user,this->channelsArray.begin(), this->channelsArray.end());
	else
		printNames(*server, user, server->getChannels().begin(), server->getChannels().end());
}

void	IRC::ChannelNames::parseArgs(IRC::Server* server)
{
	std::vector<std::string> argsArray = splitString(args, " ");
	std::vector<std::string> channelsArrayStr = splitString(argsArray[0], ",");

	std::vector<Channel>::iterator channelIt;
	for (std::vector<std::string>::iterator it = channelsArrayStr.begin(); it != channelsArrayStr.end(); it++)
	{
		channelIt = server->getChannelIt(*it);
		if (channelIt == server->getChannels().end())
			continue;
		this->channelsArray.push_back(*channelIt);
	}
}

void	IRC::ChannelNames::printNames(IRC::Server server, IRC::User user, std::vector<Channel>::iterator itBegin, std::vector<Channel>::iterator itEnd)
{
	for (std::vector<Channel>::iterator it = itBegin; it != itEnd; it++)
	{
		// TODO: private (+p) check
		
		if (it->isSecret() && !user.isInChannel(*it))
			continue;
		setReply(RPL_NAMREPLY, server, user, 2, it->getName().c_str(), it->getUsersString().c_str());
		setReply(RPL_ENDOFNAMES, server, user, 1, it->getName().c_str());
	}
}
