/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:15:21 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/12 18:15:03 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelJoin.hpp"


IRC::ChannelJoin::ChannelJoin() {}
IRC::ChannelJoin::ChannelJoin(const IRC::ChannelJoin &other) { *this = other; }
IRC::ChannelJoin::~ChannelJoin() {}

IRC::ChannelJoin &IRC::ChannelJoin::operator=(const IRC::ChannelJoin &other)
{
	if (this != &other)
	{
		channelsArray = other.channelsArray;
		passwordsArray = other.passwordsArray;
	}
	return *this;
}

void			IRC::ChannelJoin::exec(IRC::Server* server, IRC::User& user)
{
	/** CHECK AUTHENTICATION **/
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, *server, user, 0);

	/** PARSE ARGS (channels and passwords) **/
	if (parseArgs(*server, user) < 0)
		return ;

	/** ITERATE EACH PARSED CHANNEL **/
	for (size_t i = 0; i < channelsArray.size(); i++)
	{
		if (channelsArray[i].size() < 2 || channelsArray[i].at(0) != '#')
			return setError(ERR_BADCHANMASK, *server, user, 1, channelsArray[i].c_str());

		if (user.getJoinedChannels().size() >= MAX_CHANNELS)
			return setError(ERR_TOOMANYCHANNELS, *server, user, 1, channelsArray[i].c_str());

		/** IF CHANNEL ALREADY EXIST, JOIN. IF DOESNT EXIST, CREATE. **/
		std::vector<IRC::Channel>::iterator found = std::find(server->getChannels().begin(), server->getChannels().end(), Channel(channelsArray[i], User()));
		IRC::Channel newChannel;
		if (found != server->getChannels().end())
			newChannel = joinExistingChannel(*found, *server, user);
		else
			newChannel = createNewChannel(channelsArray[i], user, server);

		if (newChannel == Channel())
			return ;
		
		newChannel.broadcastAction(server, user, "JOIN");
		
		if (newChannel.getTopic().size() == 0)
			setReply(RPL_NOTOPIC, *server, user, 1, newChannel.getName().c_str());
		else
			setReply(RPL_TOPIC, *server, user, 2, newChannel.getName().c_str(), newChannel.getTopic().c_str());
			
		setReply(RPL_NAMREPLY, *server, user, 2, newChannel.getName().c_str(), newChannel.getUsersString().c_str());
		setReply(RPL_ENDOFNAMES, *server, user, 1, newChannel.getName().c_str());
	}
}

int				IRC::ChannelJoin::parseArgs(IRC::Server server, IRC::User user)
{
	std::vector<std::string> argsArray = splitString(args, " ");
	
	if (argsArray.size() < 1 || argsArray[0].size() == 0)
	{
		setError(ERR_NEEDMOREPARAMS, server, user, 1, command.c_str());
		return -1;
	}
	
	channelsArray = splitString(argsArray[0], ",");
	
	if (argsArray.size() > 1)
		passwordsArray = splitString(argsArray[1], ",");

	return 0;
}

IRC::Channel	IRC::ChannelJoin::joinExistingChannel(IRC::Channel& channel, IRC::Server server, IRC::User& user)
{
	if (channel.isInviteOnly())
	{
		setError(ERR_INVITEONLYCHAN, server, user, 1, channel.getName().c_str());
		return Channel();
	}

	// TODO: ERR_BANNEDFROMCHAN: the user's nick/username/hostname must not match any active bans;
	
	if (!channel.checkPassword("") && (passwordsArray.size() <= 0 || !channel.checkPassword(passwordsArray.at(0))))
	{
		setError(ERR_BADCHANNELKEY, server, user, 1, channel.getName().c_str());
		return Channel();
	}
	else if (passwordsArray.size() > 0)
		passwordsArray.erase(passwordsArray.begin());

	if (channel.isFull())
	{
		setError(ERR_CHANNELISFULL, server, user, 1, channel.getName().c_str());
		return Channel();
	}

	if (channel.existsUser(user))
		return Channel();

	channel.addUser(user);
	user.addJoinedChannel(channel);
	
	return channel;
}

IRC::Channel	IRC::ChannelJoin::createNewChannel(std::string channelName, IRC::User& user, IRC::Server* server)
{
	IRC::Channel newChannel = Channel(channelName, user);
	server->addChannel(newChannel);
	user.addJoinedChannel(newChannel);

	return newChannel;
}

/*
 TODO:
join #a,#b,#c,#d
:kepa!kepa@1Sb.j18.j49ElA.virtual JOIN :#a
:glencoe.chathispano.com 353 kepa = #a :@Guest48 kepa
:glencoe.chathispano.com 366 kepa #a :End of /NAMES list.
:kepa!kepa@1Sb.j18.j49ElA.virtual JOIN :#b
:glencoe.chathispano.com 353 kepa = #b :@Guest48 kepa
:glencoe.chathispano.com 366 kepa #b :End of /NAMES list.
:kepa!kepa@1Sb.j18.j49ElA.virtual JOIN :#c
:glencoe.chathispano.com 332 kepa #c :https://www.technovelty.org/c/relocation-truncated-to-fit-wtf.html // Resuenan las llamadas a funcion, chirrian los bucles, retumban los return, soplan vapor los punteros.
:glencoe.chathispano.com 333 kepa #c makemake.chathispano.com :1455528292
:glencoe.chathispano.com 353 kepa = #c :@Dreg GertY-3000 beastie PouJohn @micronn Guest48 bbb_ sinkmanu R2-D2 kepa
:glencoe.chathispano.com 366 kepa #c :End of /NAMES list.
:glencoe.chathispano.com NOTICE kepa :Bienvenido al canal de programacion en lenguaje C. Foro del canal: http://canalc.hispla.com
:kepa!kepa@1Sb.j18.j49ElA.virtual JOIN :#d
:glencoe.chathispano.com 353 kepa = #d :@Guest48 kepa
:glencoe.chathispano.com 366 kepa #d :End of /NAMES list.
*/
