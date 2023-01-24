/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:15:21 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/24 17:41:09 by karisti-         ###   ########.fr       */
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
	// CHECK AUTHENTICATION //
	/*
	if (!user.isAuthenticated())
	{
		// 451     ERR_NOTREGISTERED
		std::cout << "451 * JOIN :You have not registered." << std::endl;
		return ;
	}
	*/

	// PARSE ARGS (channels and passwords) //
	std::vector<std::string> argsArray = splitString(args, " ");
	if (argsArray.size() < 1 || argsArray[0].size() == 0)
	{
		// 461     ERR_NEEDMOREPARAMS  "<client> <command> :Not enough parameters"
		std::cout << "461 * JOIN :Not enough parameters." << std::endl;
		return ;
	}
	
	std::cout << "Channels: " << std::endl;
	std::vector<std::string> channelsArray = splitString(argsArray[0], ",");
	
	std::vector<std::string> passwordsArray;
	if (argsArray.size() > 1)
	{
		std::cout << "Passwords: " << std::endl;
		passwordsArray = splitString(argsArray[1], ",");
	}
	

	// ITERATE EACH PARSED CHANNEL //
	for (size_t i = 0, j = 0; i < channelsArray.size(); i++)
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
			if (found->isInviteOnly())
			{
				// 473     ERR_INVITEONLYCHAN
				std::cout << "<client> <channel> :Cannot join channel (+i)" << std::endl;
				return ;
			}
			if (!found->checkPassword("") && (j >= passwordsArray.size() - 1 || !found->checkPassword(passwordsArray[j++])))
			{
				// 475     ERR_BADCHANNELKEY
				std::cout << "<client> <channel> :Cannot join channel (+k)" << std::endl;
				return ;
			}
			found->addUser(user.getNick());
		}
		else
		{
			IRC::Channel newChannel = Channel(channelsArray[i], user.getNick());
			newChannel.addUser(user.getNick());
			server->getChannels().push_back(newChannel);
		}
	}	
}
