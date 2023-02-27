/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelPart.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:19:43 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/27 18:01:34 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelPart.hpp"


IRC::ChannelPart::ChannelPart() {}
IRC::ChannelPart::~ChannelPart() {}

void	IRC::ChannelPart::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, *server, user, 0);

	std::vector<std::string> argsArray = splitString(args, " ");
	if (argsArray.size() < 1)
		return setError(ERR_NEEDMOREPARAMS, *server, user, 1, command.c_str());
	
	std::vector<std::string> channelsArray = splitString(argsArray[0], ",");

	std::vector<Channel>::iterator channelIt;
	/** ITERATE EACH PARSED CHANNEL **/
	for (std::vector<std::string>::iterator it = channelsArray.begin(); it != channelsArray.end(); it++)
	{
		// TODO now:
		// std::transform(it->begin(), it->end(), it->begin(), ::tolower);
		channelIt = server->findChannel(*it);
		if (channelIt == server->getChannels().end())
			return setError(ERR_NOSUCHCHANNEL, *server, user, 1, (*it).c_str());
		
		if (!channelIt->existsUser(user))
			return setError(ERR_NOTONCHANNEL, *server, user, 1, (*it).c_str());
		
		setActionInReply(*server, user, *channelIt, "PART :" + channelIt->getName());
		
		channelIt->removeUser(server, user);
	}
}
