/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelKick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:19:51 by karisti-          #+#    #+#             */
/*   Updated: 2023/03/01 11:21:24 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelKick.hpp"


IRC::ChannelKick::ChannelKick() {}
IRC::ChannelKick::~ChannelKick() {}

void	IRC::ChannelKick::exec(IRC::Server* server, IRC::User& user)
{
	/** CHECK ALL POSSIBLE ERRORS **/
	if (!user.isAuthenticated())
		return setReply(ERR_NOTREGISTERED, *server, user, 0);

	std::vector<std::string> argsArray = splitString(args, " ", 2);
	if (argsArray.size() < 2)
		return setReply(ERR_NEEDMOREPARAMS, *server, user, 1, this->command.c_str());

	if (argsArray[0].size() < 2 || argsArray[0].at(0) != '#')
		return setReply(ERR_BADCHANMASK, *server, user, 1, argsArray[0].c_str());

	std::map<std::string, IRC::Channel>::iterator channel = server->findChannel(argsArray[0]);
	if (channel == server->getChannels().end())
		return setReply(ERR_NOSUCHCHANNEL, *server, user, 1, argsArray[0].c_str());

	if (!user.isInChannel(channel->second))
		return setReply(ERR_NOTONCHANNEL, *server, user, 1, channel->second.getName().c_str());

	if (!channel->second.isOperator(user))
		return setReply(ERR_CHANOPRIVSNEEDED, *server, user, 1, channel->second.getName().c_str());

	std::vector<IRC::User>::iterator victimIt = findUser(server->getUsers(), argsArray[1]);
	if (victimIt == server->getUsers().end() || !victimIt->isInChannel(channel->second.getName()))
		return setReply(ERR_USERNOTINCHANNEL, *server, user, 2, argsArray[1].c_str(), channel->second.getName().c_str());
	
	/** USER IS REMOVED FROM CHANNEL AND REPLY IS SENT **/
	if (argsArray.size() < 3)
		setActionInReply(*server, user, channel->second, "KICK " + channel->second.getName() + " " + victimIt->getNick() + " " + user.getNick());
	else
		setActionInReply(*server, user, channel->second, "KICK " + channel->second.getName() + " " + victimIt->getNick() + " " + argsArray[2]);

	channel->second.removeUser(server, *victimIt);
}
