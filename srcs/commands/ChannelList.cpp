/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:46:03 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/31 21:08:56 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelList.hpp"

IRC::ChannelList::ChannelList()
{
}

IRC::ChannelList::~ChannelList()
{
}

void IRC::ChannelList::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, 0);
	
	parseArgs(server);
	
	if (this->channelsArray.size() > 0)
		printNames(this->channelsArray.begin(), this->channelsArray.end());
	else
		printNames(server->getChannels().begin(), server->getChannels().end());
}

void	IRC::ChannelList::parseArgs(IRC::Server* server)
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

void	IRC::ChannelList::printNames(std::vector<Channel>::iterator itBegin, std::vector<Channel>::iterator itEnd)
{
	setReply(RPL_LISTSTART, 0);
	
	for (std::vector<Channel>::iterator it = itBegin; it != itEnd; it++)
	{
		/*
		TODO: Private  channels  are  listed  (without  their
		topics)  as channel "Prv" unless the client generating the query is
		actually on that channel.
		*/
		
		if (it->isSecret())
			continue ;
		
		std::stringstream ss;
		ss << it->getUsers().size();
		std::string sizeStr = ss.str();
		
		setReply(RPL_LIST, 3, it->getName().c_str(), sizeStr.c_str(), it->getTopic().c_str());
	}
	
	setReply(RPL_LISTEND, 0);
}
