/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:15:21 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/25 09:58:38 by karisti-         ###   ########.fr       */
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
	PASS
	NICK <nick>
	USER <username> 0 * <realname>
*/

/*
	Comando: JOIN
	Parámetros: <canal>{,<canal>} [<clave>{,<clave>}]
*/
void IRC::ChannelJoin::exec(IRC::Server* server, IRC::User& user)
{
	// TODO: Solo para pruebas, borrar cuando la autenticacion este bien.
	user.setNick("karisti"),
	user.setPassword("pass");
	user.changeAuthenticated();
	// **              ** //
	
	// CHECK AUTHENTICATION //
	/*
	if (!user.isAuthenticated())
	{
		// 451     ERR_NOTREGISTERED
		std::cout << "451 * JOIN :You have not registered." << std::endl;
		return ;
	}
	*/

	if (parseArgs() < 0)
		return ;

	// ITERATE EACH PARSED CHANNEL //
	for (size_t i = 0; i < channelsArray.size(); i++)
	{
		if (channelsArray[i].size() < 2)
			continue ;
		if (channelsArray[i].at(0) != '#')
		{
			// 476     ERR_BADCHANMASK    "<channel> :Bad Channel Mask"
			std::cout << "476 karisti test :Invalid channel name." << std::endl;
			return ;
		}
		
		channelsArray[i].erase(0, 1); // erase #
		
		// IF CHANNEL ALREADY EXIST, JOIN. IF DOESNT EXIST, CREATE. //
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

/** PARSE ARGS (channels and passwords) **/
int	IRC::ChannelJoin::parseArgs(void)
{
	std::vector<std::string> argsArray = splitString(args, " ", -1);
	
	if (argsArray.size() < 1 || argsArray[0].size() == 0)
	{
		// 461	ERR_NEEDMOREPARAMS  "<client> <command> :Not enough parameters"
		std::cout << "461 * JOIN :Not enough parameters." << std::endl;
		return -1;
	}
	
	channelsArray = splitString(argsArray[0], ",", -1);
	
	if (argsArray.size() > 1)
		passwordsArray = splitString(argsArray[1], ",", -1);

	return 0;
}

int		IRC::ChannelJoin::joinExistingChannel(IRC::Channel& channel, std::string nick)
{
	if (channel.isInviteOnly())
	{
		// 473     ERR_INVITEONLYCHAN
		std::cout << "<client> <channel> :Cannot join channel (+i)" << std::endl;
		return -1;
	}
	
	if (!channel.checkPassword("") && (passwordsArray.size() <= 0 || !channel.checkPassword(passwordsArray.at(0))))
	{
		// 475     ERR_BADCHANNELKEY
		std::cout << "<client> <channel> :Cannot join channel (+k)" << std::endl;
		return -1;
	}
	else if (passwordsArray.size() > 0)
		passwordsArray.erase(passwordsArray.begin());

	std::vector<std::string>::iterator found = std::find(channel.getUsers().begin(), channel.getUsers().end(), nick);
	if (found == channel.getUsers().end())
		channel.addUser(nick);
	return 0;
}

int		IRC::ChannelJoin::createNewChannel(std::string channelName, std::string nick, std::vector<IRC::Channel>& channels)
{
	IRC::Channel newChannel = Channel(channelName, nick);
	newChannel.addUser(nick);
	channels.push_back(newChannel);
	return 0;
}