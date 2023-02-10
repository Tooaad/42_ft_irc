/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelPart.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:19:43 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/10 18:59:59 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelPart.hpp"


IRC::ChannelPart::ChannelPart() {}
IRC::ChannelPart::ChannelPart(const IRC::ChannelPart &other) { *this = other; }
IRC::ChannelPart::~ChannelPart() {}

IRC::ChannelPart &IRC::ChannelPart::operator=(const IRC::ChannelPart &other)
{
	if (this != &other)
		channelsArray = other.channelsArray;
	return *this;
}

void	IRC::ChannelPart::exec(Server* server, User* user)
{
	/** CHECK AUTHENTICATION **/
	if (!user->isAuthenticated())
		return setError(ERR_NOTREGISTERED, server, user, 0);

	/** PARSE ARGS (channels and passwords) **/
	if (parseArgs(server, user) < 0)
		return ;

	std::vector<Channel*>::iterator channelIt;
	/** ITERATE EACH PARSED CHANNEL **/
	for (std::vector<std::string>::iterator it = channelsArray.begin(); it != channelsArray.end(); it++)
	{
		channelIt = server->getChannelIt(*it); // TODO now; error si no existe el canal, no se detecta
		if (channelIt == server->getChannels().end())
			return setError(ERR_NOSUCHCHANNEL, server, user, 1, (*it).c_str());
		
		if (!(*channelIt)->existsUser(user))
			return setError(ERR_NOTONCHANNEL, server, user, 1, (*it).c_str());
		
		(*channelIt)->broadcastAction(server, *user, "PART");
		(*channelIt)->removeUser(server, user);
		
		std::cout << "VAMOS BIEN" << std::endl;
	}
}

int		IRC::ChannelPart::parseArgs(IRC::Server* server, IRC::User* user)
{
	std::vector<std::string> argsArray = splitString(args, " ");
	
	if (argsArray.size() < 1 || argsArray[0].size() == 0)
	{
		setError(ERR_NEEDMOREPARAMS, server, user, 1, command.c_str());
		return -1;
	}
	
	channelsArray = splitString(argsArray[0], ",");

	return 0;
}
