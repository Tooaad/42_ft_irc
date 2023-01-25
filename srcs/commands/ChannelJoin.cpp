/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:15:21 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/25 20:22:53 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelJoin.hpp"

IRC::ChannelJoin::ChannelJoin()
{
}

IRC::ChannelJoin::~ChannelJoin()
{
}

/*
	Comando: JOIN
	Parámetros: <canal>{,<canal>} [<clave>{,<clave>}]
*/
void IRC::ChannelJoin::exec(IRC::Server* server, IRC::User& user)
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

	/** ITERATE EACH PARSED CHANNEL **/
	for (size_t i = 0; i < channelsArray.size(); i++)
	{
		if (channelsArray[i].size() < 2 || channelsArray[i].at(0) != '#')
		{
			setError(ERR_BADCHANMASK, 1, channelsArray[i].c_str());
			return ;
		}
		
		channelsArray[i].erase(0, 1); // erase #
		
		/** IF CHANNEL ALREADY EXIST, JOIN. IF DOESNT EXIST, CREATE. **/
		std::vector<IRC::Channel>::iterator found = std::find(server->getChannels().begin(), server->getChannels().end(), Channel(channelsArray[i], ""));
		if (found != server->getChannels().end())
		{
			if (joinExistingChannel(*found, user.getNick()) < 0)
				return ;
		}
		else
		{
			if (createNewChannel(channelsArray[i], user.getNick(), server->getChannels()))
				return ;
		}
	}
}

int	IRC::ChannelJoin::parseArgs(void)
{
	std::vector<std::string> argsArray = splitString(args, " ");
	
	if (argsArray.size() < 1 || argsArray[0].size() == 0)
	{
		setError(ERR_NEEDMOREPARAMS, 1, command.c_str());
		return -1;
	}
	
	channelsArray = splitString(argsArray[0], ",");
	
	if (argsArray.size() > 1)
		passwordsArray = splitString(argsArray[1], ",");

	return 0;
}

int		IRC::ChannelJoin::joinExistingChannel(IRC::Channel& channel, std::string nick)
{
	
	if (channel.isInviteOnly())
	{
		setError(ERR_INVITEONLYCHAN, 1, channel.getName().c_str());
		return -1;
	}
	
	if (!channel.checkPassword("") && (passwordsArray.size() <= 0 || !channel.checkPassword(passwordsArray.at(0))))
	{
		setError(ERR_BADCHANNELKEY, 1, channel.getName().c_str());
		return -1;
	}
	else if (passwordsArray.size() > 0)
		passwordsArray.erase(passwordsArray.begin());

	if (!channel.existUser(nick))
		channel.addUser(nick);
	
	printChannel(channel);
	return 0;
}

int		IRC::ChannelJoin::createNewChannel(std::string channelName, std::string nick, std::vector<IRC::Channel>& channels)
{
	IRC::Channel newChannel = Channel(channelName, nick);
	newChannel.addUser(nick);
	channels.push_back(newChannel);
	return 0;
}
