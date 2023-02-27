/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelInvite.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:20:01 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/27 14:11:50 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelInvite.hpp"


IRC::ChannelInvite::ChannelInvite() {}
IRC::ChannelInvite::~ChannelInvite() {}

void	IRC::ChannelInvite::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, *server, user, 0);
	
	std::vector<std::string> argsArray = splitString(args, " ");
	if (argsArray.size() < 2)
		return setError(ERR_NEEDMOREPARAMS, *server, user, 1, this->command.c_str());

	std::vector<IRC::Channel>::iterator channel = server->getChannelIt(argsArray[1]);
	if (channel == server->getChannels().end())
		return setError(ERR_NOSUCHCHANNEL, *server, user, 1, argsArray[1].c_str());

	std::vector<IRC::User>::iterator newUserIt = findUser(server->getUsers(), argsArray[0]);
	if (newUserIt == server->getUsers().end())
		return setError(ERR_NOSUCHNICK, *server, user, 1, argsArray[0].c_str());

	if (!user.isInChannel(*channel))
		return setError(ERR_NOTONCHANNEL, *server, user, 1, channel->getName().c_str());

	if (channel->isInviteOnly() && !channel->isOperator(user))
		return setError(ERR_CHANOPRIVSNEEDED, *server, user, 1, channel->getName().c_str());

	if (channel->existsUser(*newUserIt))
		return setError(ERR_USERONCHANNEL, *server, user, 2, newUserIt->getNick().c_str(), channel->getName().c_str());

	
	std::string action = ":" + user.getNick() + "!" + user.getUser() + "@" + user.getHostname() + " INVITE " + newUserIt->getNick() + " :" + channel->getName();
	newUserIt->addInvitedChannel(*channel);
	newUserIt->sendMessage(action);
	
	setReply(RPL_INVITING, *server, user, 2, newUserIt->getNick().c_str(), channel->getName().c_str());
}
