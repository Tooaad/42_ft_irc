/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:15:21 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/31 14:31:53 by karisti-         ###   ########.fr       */
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
		return setError(ERR_NOTREGISTERED, 0);

	/** PARSE ARGS (channels and passwords) **/
	if (parseArgs() < 0)
		return ;

	/** ITERATE EACH PARSED CHANNEL **/
	for (size_t i = 0; i < channelsArray.size(); i++)
	{
		if (channelsArray[i].size() < 2 || channelsArray[i].at(0) != '#')
			return setError(ERR_BADCHANMASK, 1, channelsArray[i].c_str());

		if (user.getJoinedChannels().size() >= MAX_CHANNELS)
			return setError(ERR_TOOMANYCHANNELS, 1, channelsArray[i].c_str());

		
		/** IF CHANNEL ALREADY EXIST, JOIN. IF DOESNT EXIST, CREATE. **/
		std::vector<IRC::Channel>::iterator found = std::find(server->getChannels().begin(), server->getChannels().end(), Channel(channelsArray[i], User()));
		IRC::Channel* newChannel;
		if (found != server->getChannels().end())
			newChannel = joinExistingChannel(*found, user);
		else
			newChannel = createNewChannel(channelsArray[i], user, server);

		if (newChannel != NULL)
		{
			newChannel->broadcastAction(server, user, "JOIN");
			
			if (newChannel->getTopic().size() == 0)
				setReply(RPL_NOTOPIC, 1, newChannel->getName().c_str());
			else
				setReply(RPL_TOPIC, 2, newChannel->getName().c_str(), newChannel->getTopic().c_str());
				
			setReply(RPL_NAMREPLY, 2, newChannel->getName().c_str(), newChannel->getUsersString().c_str());
			setReply(RPL_ENDOFNAMES, 1, newChannel->getName().c_str());
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

IRC::Channel*	IRC::ChannelJoin::joinExistingChannel(IRC::Channel& channel, IRC::User& user)
{
	if (channel.isInviteOnly())
	{
		setError(ERR_INVITEONLYCHAN, 1, channel.getName().c_str());
		return NULL;
	}

	// TODO: ERR_BANNEDFROMCHAN: the user's nick/username/hostname must not match any active bans;
	
	if (!channel.checkPassword("") && (passwordsArray.size() <= 0 || !channel.checkPassword(passwordsArray.at(0))))
	{
		setError(ERR_BADCHANNELKEY, 1, channel.getName().c_str());
		return NULL;
	}
	else if (passwordsArray.size() > 0)
		passwordsArray.erase(passwordsArray.begin());

	if (channel.isFull())
	{
		setError(ERR_CHANNELISFULL, 1, channel.getName().c_str());
		return NULL;
	}

	if (channel.existsUser(user))
		return NULL;

	channel.addUser(user, IRC::Channel::NORMAL_USER);
	user.addJoinedChannel(channel);
	
	return &channel;
}

IRC::Channel*	IRC::ChannelJoin::createNewChannel(std::string channelName, IRC::User& user, IRC::Server* server)
{
	// TODO: Cuidado leaks
	IRC::Channel* newChannel = new Channel(channelName, user);
	server->addChannel(*newChannel);
	user.addJoinedChannel(*newChannel);

	return newChannel;
}
