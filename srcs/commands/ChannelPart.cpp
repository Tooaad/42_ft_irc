/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelPart.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:19:43 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/27 18:34:15 by karisti-         ###   ########.fr       */
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


	std::vector<Channel>::iterator channel;
	/** ITERATE EACH PARSED CHANNEL **/
	for (std::vector<std::string>::iterator it = channelsArray.begin(); it != channelsArray.end(); it++)
	{
		channel = server->getChannelIt(*it);
		if (channel == server->getChannels().end())
		{
			setError(ERR_NOSUCHCHANNEL, 1, (*it).c_str());
			return ;
		}
		
		if (!channel->existsUser(user))
		{
			setError(ERR_NOTONCHANNEL, 1, (*it).c_str());
			return ;
		}
		
		channel->removeUser(user);
		if (channel->getUsers().empty())
			server->removeChannel(*channel);
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
