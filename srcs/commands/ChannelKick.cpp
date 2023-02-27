/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelKick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:19:51 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/27 13:17:56 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelKick.hpp"


IRC::ChannelKick::ChannelKick() {}
IRC::ChannelKick::~ChannelKick() {}


void	IRC::ChannelKick::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, *server, user, 0);

	std::vector<std::string> argsArray = splitString(args, " ", 2);
	if (argsArray.size() < 2)
		return setError(ERR_NEEDMOREPARAMS, *server, user, 1, this->command.c_str());

	if (argsArray[0].size() < 2 || argsArray[0].at(0) != '#')
		return setError(ERR_BADCHANMASK, *server, user, 1, argsArray[0].c_str());

	std::vector<IRC::Channel>::iterator channel = server->getChannelIt(argsArray[0]);
	if (channel == server->getChannels().end())
		return setError(ERR_NOSUCHCHANNEL, *server, user, 1, argsArray[0].c_str());

	if (!user.isInChannel(*channel))
		return setError(ERR_NOTONCHANNEL, *server, user, 1, channel->getName().c_str());

	if (!channel->isOperator(user))
		return setError(ERR_CHANOPRIVSNEEDED, *server, user, 1, channel->getName().c_str());

	std::vector<IRC::User>::iterator victimIt = findUser(channel->getUsers(), argsArray[1]);
	if (victimIt == channel->getUsers().end())
		return setError(ERR_USERNOTINCHANNEL, *server, user, 2, argsArray[1].c_str(), channel->getName().c_str());
	
	
	if (argsArray.size() < 3)
		setActionInReply(*server, user, *channel, "KICK " + channel->getName() + " " + victimIt->getNick() + " " + user.getNick());
	else
		setActionInReply(*server, user, *channel, "KICK " + channel->getName() + " " + victimIt->getNick() + " " + argsArray[2]);

	channel->removeUser(server, *victimIt);
}
