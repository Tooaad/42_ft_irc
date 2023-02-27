/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:46:03 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/27 18:01:33 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelList.hpp"


IRC::ChannelList::ChannelList() {}
IRC::ChannelList::~ChannelList() {}

void	IRC::ChannelList::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, *server, user, 0);
	
	std::vector<std::string> argsArray = splitString(args, " ");
	std::vector<std::string> channelsArrayStr = splitString(argsArray[0], ",");
	std::vector<Channel> channelsArray;
	
	std::vector<Channel>::iterator channelIt;
	for (std::vector<std::string>::iterator it = channelsArrayStr.begin(); it != channelsArrayStr.end(); it++)
	{
		channelIt = server->findChannel(*it);
		if (channelIt == server->getChannels().end())
			continue;
		channelsArray.push_back(*channelIt);
	}
	
	if (channelsArray.size() > 0)
		printList(*server, user, channelsArray.begin(), channelsArray.end());
	else
		printList(*server, user, server->getChannels().begin(), server->getChannels().end());
}

void	IRC::ChannelList::printList(IRC::Server server, IRC::User user, std::vector<IRC::Channel>::iterator itBegin, std::vector<IRC::Channel>::iterator itEnd)
{
	setReply(RPL_LISTSTART, server, user, 0);
	
	for (std::vector<Channel>::iterator it = itBegin; it != itEnd; it++)
	{
		if (it->isSecret() && !user.isInChannel(*it))
			continue ;
		
		std::stringstream ss;
		ss << it->getUsers().size();
		std::string sizeStr = ss.str();
		
		setReply(RPL_LIST, server, user, 3, it->getName().c_str(), sizeStr.c_str(), it->getTopic().c_str());
	}
	
	setReply(RPL_LISTEND, server, user, 0);
}
