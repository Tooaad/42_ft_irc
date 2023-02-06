/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:26 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/06 18:38:43 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

IRC::User::User(void) { User(0); }
IRC::User::User(const IRC::User& other) { *this = other; }
IRC::User::~User() {}

IRC::User::User(int socket)
{
	this->socket = socket;
	this->password = "";
	this->nick = "";
	this->user = "";
	this->realname = "";
	this->hostname = "";
	this->servername = "";
	this->authenticated = false;
	this->invisible = false;
	this->op = false;
	this->subscribe = false;
	this->timeout = 0;
	this->buffer = "";
}

IRC::User& IRC::User::operator=(const IRC::User &other)
{
	this->socket = other.socket;
	this->password = other.password;
	this->nick = other.nick;
	this->user = other.user;
	this->realname = other.realname;
	this->hostname = other.hostname;
	this->servername = other.servername;
	this->authenticated = other.authenticated;
	this->invisible = other.invisible;
	this->op = other.op;
	this->subscribe = other.subscribe;
	this->timeout = other.timeout;
	this->joinedChannels = other.joinedChannels;
	this->buffer = other.buffer;
	
	return *this;
}


int IRC::User::getSocket(void) const
{
	return this->socket;
}

std::string IRC::User::getPassword(void) const
{
	return this->password;
}

std::string IRC::User::getNick(void) const
{
	return this->nick;
}

std::string IRC::User::getUser(void) const
{
	return this->user;
}

std::string IRC::User::getRealname(void) const
{
	return this->realname;
}

std::string IRC::User::getHostname(void) const
{
	return this->hostname;
}

std::string IRC::User::getServername(void) const
{
	return this->servername;
}

time_t IRC::User::getTimeout(void) const
{
	return this->timeout;
}

bool IRC::User::isAuthenticated(void) const
{
	return this->authenticated;
}

bool IRC::User::isInvisible(void) const
{
	return this->invisible;
}

bool IRC::User::isSubscribed(void) const
{
	return this->subscribe;
}

bool IRC::User::isOp(void) const
{
	return this->op;
}

std::vector<IRC::Channel> IRC::User::getJoinedChannels(void) const
{
	return this->joinedChannels;
}

void IRC::User::setPassword(std::string password)
{
	this->password = password;
}

void IRC::User::setNick(std::string nick)
{
	this->nick = nick;
}

void IRC::User::setUser(std::string user)
{
	this->user = user;
}

void IRC::User::setRealname(std::string realname)
{
	this->realname = realname;
}

void IRC::User::setHostname(std::string hostname)
{
	this->hostname = hostname;
}

void IRC::User::setServername(std::string servername)
{
	this->servername = servername;
}

void IRC::User::setTimeout(time_t timeout)
{
	this->timeout = timeout;
}

void IRC::User::changeAuthenticated()
{
	this->authenticated = !authenticated;
}

void IRC::User::changeInvisibility()
{
	this->invisible = !invisible;
}

void IRC::User::changeSubscription()
{
	this->subscribe = !subscribe;
}

void IRC::User::deOp()
{
	this->op = false;
}

void IRC::User::addJoinedChannel(IRC::Channel& channel)
{
	std::vector<IRC::Channel>::iterator found = std::find(joinedChannels.begin(), joinedChannels.end(), channel);
	
	if (found == joinedChannels.end())
		joinedChannels.push_back(channel);
	
}

void IRC::User::removeJoinedChannel(IRC::Channel channel)
{
	std::vector<IRC::Channel>::iterator found = std::find(joinedChannels.begin(), joinedChannels.end(), channel);
	
	if (found != joinedChannels.end())
		this->joinedChannels.erase(found);
}

std::string	IRC::User::getJoinedChannelsString(void)
{
	std::string channelsString = "";
	
	for (std::vector<IRC::Channel>::const_iterator channel_it = joinedChannels.begin(); channel_it != joinedChannels.end(); ++channel_it)
	{
		channelsString += channel_it->getName();
		if (channel_it + 1 != joinedChannels.end())
			channelsString += " ";
	}

	return channelsString;
}

bool IRC::User::isInChannel(IRC::Channel channel)
{
	if (std::find(joinedChannels.begin(), joinedChannels.end(), channel) != joinedChannels.end())
		return true;
	return false;
}

std::string	IRC::User::getBuffer(void) const { return this->buffer; }
void		IRC::User::appendBuffer(std::string str) { this->buffer.append(str); }
void		IRC::User::clearBuffer(void) { this->buffer.clear(); }

bool IRC::operator== (const IRC::User lhs, const IRC::User rhs) {
	if (lhs.getSocket() != rhs.getSocket())
		return false;
	return true;
}

IRC::User IRC::findUser(std::vector<IRC::User> users, std::string nick)
{
	std::vector<IRC::User>::iterator it = users.begin();
	int i = 0;
	for (; it != users.end(); it++, i++)
	{
		if ((*it).getNick() == nick)
			return *it;
	}
	return *it;
}

void	IRC::printUsers(std::vector<IRC::User> users)
{
	if (users.size() == 0)
		return ;

	std::cout << "------- Users -------" << std::endl;
	std::vector<IRC::User>::iterator it = users.begin();
	for (; it != users.end(); it++)
		printUser(*it);
	std::cout << "---------------------" << std::endl;
}

void	IRC::printUser(IRC::User user)
{
	std::cout << "Socket: " << user.getSocket();
	std::cout << ", Password: " << user.getPassword();
	std::cout << ", Nick: " << user.getNick();
	std::cout << ", User: " << user.getUser();
	std::cout << ", Real name: " << user.getRealname();
	std::cout << ", Authenticated: " << user.isAuthenticated();
	std::cout << ", Channels: " << user.getJoinedChannelsString();
	std::cout << std::endl;
}
