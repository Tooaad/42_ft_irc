/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:46:03 by karisti-          #+#    #+#             */
/*   Updated: 2023/03/01 11:29:15 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelList.hpp"


IRC::ChannelList::ChannelList() {}
IRC::ChannelList::~ChannelList() {}

void	IRC::ChannelList::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setReply(ERR_NOTREGISTERED, *server, user, 0);
	
	std::vector<std::string> argsArray = splitString(args, " ");
	std::vector<std::string> channelsArrayStr = splitString(argsArray[0], ",");
	std::map<std::string, IRC::Channel> channelsArray;
	
	for (std::vector<std::string>::iterator it = channelsArrayStr.begin(); it != channelsArrayStr.end(); it++)
	{
		std::map<std::string, IRC::Channel>::iterator channelIt = server->findChannel(*it);
		if (channelIt != server->getChannels().end())
			channelsArray[channelIt->second.getName()] = channelIt->second;
	}
	
	if (channelsArray.size() > 0)
		printList(*server, user, channelsArray.begin(), channelsArray.end());
	else
		printList(*server, user, server->getChannels().begin(), server->getChannels().end());
}

void	IRC::ChannelList::printList(IRC::Server server, IRC::User user, std::map<std::string, IRC::Channel>::iterator itBegin, std::map<std::string, IRC::Channel>::iterator itEnd)
{
	setReply(RPL_LISTSTART, server, user, 0);
	
	for (std::map<std::string, IRC::Channel>::iterator it = itBegin; it != itEnd; it++)
	{
		if (it->second.isSecret() && !user.isInChannel(it->second))
			continue ;
		
		std::stringstream ss;
		ss << it->second.getUsers().size();
		std::string sizeStr = ss.str();
		
		setReply(RPL_LIST, server, user, 3, it->second.getName().c_str(), sizeStr.c_str(), it->second.getTopic().c_str());
	}
	
	setReply(RPL_LISTEND, server, user, 0);
}
