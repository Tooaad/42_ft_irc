/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelPart.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:19:43 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/27 18:12:55 by karisti-         ###   ########.fr       */
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
	{
		setError(ERR_NOTREGISTERED, 0);
		return ;
	}


	/** PARSE ARGS (channels and passwords) **/
	if (parseArgs() < 0)
		return ;


	size_t channelPos;
	/** ITERATE EACH PARSED CHANNEL **/
	for (std::vector<std::string>::iterator it = channelsArray.begin(); it != channelsArray.end(); it++)
	{
		channelPos = server->getChannelPos(*it);
		if (channelPos == (size_t) -1)
		{
			setError(ERR_NOSUCHCHANNEL, 1, (*it).c_str());
			return ;
		}
		
		if (!server->getChannels().at(channelPos).existsUser(user))
		{
			setError(ERR_NOTONCHANNEL, 1, (*it).c_str());
			return ;
		}

		IRC::Channel channel = server->getChannels().at(channelPos);
		
		channel.removeUser(user);
		if (channel.getUsers().empty())
			server->removeChannel(channel);
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
