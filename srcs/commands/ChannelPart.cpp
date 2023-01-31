/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelPart.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:19:43 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/31 11:50:28 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelPart.hpp"

IRC::ChannelPart::ChannelPart()
{
}

IRC::ChannelPart::~ChannelPart()
{
}

/*
	Command: PART
	Parameters: <channel>{,<channel>}
*/
void IRC::ChannelPart::exec(IRC::Server* server, IRC::User& user)
{
	// TODO: Solo para pruebas, borrar cuando la autenticacion este bien.
	/*
	user.setNick("karisti");
	user.setPassword("pass");
	if (!user.isAuthenticated())
		user.changeAuthenticated();
	*/
	// *************************************************************** //

	/** CHECK AUTHENTICATION **/
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, 0);

	/** PARSE ARGS (channels and passwords) **/
	if (parseArgs() < 0)
		return ;


	std::vector<Channel>::iterator channelIt;
	/** ITERATE EACH PARSED CHANNEL **/
	for (std::vector<std::string>::iterator it = channelsArray.begin(); it != channelsArray.end(); it++)
	{
		channelIt = server->getChannelIt(*it);
		if (channelIt == server->getChannels().end())
			return setError(ERR_NOSUCHCHANNEL, 1, (*it).c_str());
		
		if (!channelIt->existsUser(user))
			return setError(ERR_NOTONCHANNEL, 1, (*it).c_str());
		
		channelIt->broadcastAction(server, user, "PART");
		channelIt->removeUser(user);
		user.removeJoinedChannel(*channelIt);
		
		if (channelIt->getUsers().empty())
			server->removeChannel(*channelIt);
	}
}

int	IRC::ChannelPart::parseArgs(void)
{
	std::vector<std::string> argsArray = splitString(args, " ");
	
	if (argsArray.size() < 1 || argsArray[0].size() == 0)
	{
		setError(ERR_NEEDMOREPARAMS, 1, command.c_str());
		return -1;
	}
	
	channelsArray = splitString(argsArray[0], ",");

	return 0;
}
