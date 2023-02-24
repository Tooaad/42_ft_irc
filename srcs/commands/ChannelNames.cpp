/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelNames.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:10:20 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/24 18:42:15 by karisti-         ###   ########.fr       */
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

void	IRC::ChannelNames::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, *server, user, 0);
	
	parseArgs(server);
	
	if (this->channelsArray.size() > 0)
		printNames(*server, user);
	else
		setReply(RPL_ENDOFNAMES, *server, user, 1, "*");
	
	this->channelsArray.clear();
}

void	IRC::ChannelNames::parseArgs(IRC::Server* server)
{
	std::vector<std::string> argsArray = splitString(args, " ");
	std::vector<std::string> channelsArrayStr = splitString(argsArray[0], ",");

	std::vector<Channel>::iterator channelIt;
	for (std::vector<std::string>::iterator it = channelsArrayStr.begin(); it != channelsArrayStr.end(); it++)
	{
		if (it->size() == 0)
			continue ;
		channelIt = server->getChannelIt(*it);
		if (channelIt == server->getChannels().end())
			this->channelsArray.push_back(Channel(*it));
		else
			this->channelsArray.push_back(*channelIt);
	}
}

void	IRC::ChannelNames::printNames(IRC::Server server, IRC::User user)
{
	for (std::vector<Channel>::iterator it = this->channelsArray.begin(); it != this->channelsArray.end(); ++it)
	{
		if (it->isSecret() && !user.isInChannel(*it))
		{
			continue ;
		}

		if (it->getUsers().size() > 0)
		{
			if (user.isInChannel(*it))
				setReply(RPL_NAMREPLY, server, user, 2, it->getName().c_str(), it->getUsersString().c_str());
			else
				setReply(RPL_NAMREPLY, server, user, 2, it->getName().c_str(), it->getUsersStringVisible().c_str());
		}

		setReply(RPL_ENDOFNAMES, server, user, 1, it->getName().c_str());
	}
}
