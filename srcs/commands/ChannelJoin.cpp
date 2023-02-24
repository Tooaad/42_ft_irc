/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:15:21 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/24 19:19:17 by karisti-         ###   ########.fr       */
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

		// TODO now:
		// std::transform(this->channelsArray[i].begin(), this->channelsArray[i].end(), this->channelsArray[i].begin(), ::tolower);   // transform command type to lower anyways

		/** IF CHANNEL ALREADY EXIST, JOIN. IF DOESNT EXIST, CREATE. **/
		std::vector<IRC::Channel>::iterator found = std::find(server->getChannels().begin(), server->getChannels().end(), Channel(channelsArray[i]));
		IRC::Channel newChannel;
		if (found != server->getChannels().end())
			newChannel = joinExistingChannel(*found, *server, user);
		else
			newChannel = createNewChannel(channelsArray[i], user, server);

		if (newChannel == Channel())
			return ;
		
		setActionInReply(*server, user, newChannel, "JOIN :" + newChannel.getName());
		
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
	IRC::Channel newChannel = Channel(channelName, user, server);
	server->addChannel(newChannel);
	user.addJoinedChannel(newChannel);

	return newChannel;
}
