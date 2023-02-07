/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:26 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/07 14:11:45 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"


IRC::User::User(void) { User(0); }

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

IRC::User::User(const IRC::User& other) { *this = other; }
IRC::User::~User() {}

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

/* -- Getters -- */
int							IRC::User::getSocket(void) const { return this->socket; }
std::string					IRC::User::getPassword(void) const { return this->password; }
std::string					IRC::User::getNick(void) const { return this->nick; }
std::string					IRC::User::getUser(void) const { return this->user; }
std::string					IRC::User::getRealname(void) const { return this->realname; }
std::string					IRC::User::getHostname(void) const { return this->hostname; }
std::string					IRC::User::getServername(void) const { return this->servername; }
bool						IRC::User::isAuthenticated(void) const { return this->authenticated; }
bool						IRC::User::isInvisible(void) const { return this->invisible; }
bool						IRC::User::isOp(void) const { return this->op; }
bool						IRC::User::isSubscribed(void) const { return this->subscribe; }
time_t						IRC::User::getTimeout(void) const { return this->timeout; }
std::vector<IRC::Channel>	IRC::User::getJoinedChannels(void) const { return this->joinedChannels; }
std::string					IRC::User::getBuffer(void) const { return this->buffer; }

/* -- Setters -- */
void						IRC::User::setPassword(std::string password) { this->password = password; }
void						IRC::User::setNick(std::string nick) { this->nick = nick; }
void						IRC::User::setUser(std::string user) { this->user = user; }
void						IRC::User::setRealname(std::string realname) { this->realname = realname; }
void						IRC::User::setHostname(std::string hostname) { this->hostname = hostname; }
void						IRC::User::setServername(std::string servername) { this->servername = servername; }
void						IRC::User::changeAuthenticated(void) { this->authenticated = !authenticated; }
void						IRC::User::changeInvisibility(void) { this->invisible = !invisible; }
void						IRC::User::deOp(void) { this->op = false; }
void						IRC::User::changeSubscription(void) { this->subscribe = !subscribe; }
void						IRC::User::setTimeout(time_t timeout) { this->timeout = timeout; }

/* -- Modifiers -- */
void	IRC::User::addJoinedChannel(IRC::Channel& channel)
{
	std::vector<IRC::Channel>::iterator found = std::find(this->joinedChannels.begin(), this->joinedChannels.end(), channel);
	
	if (found == this->joinedChannels.end())
		this->joinedChannels.push_back(channel);
	
}

void	IRC::User::removeJoinedChannel(IRC::Channel channel)
{
	std::vector<IRC::Channel>::iterator found = std::find(this->joinedChannels.begin(), this->joinedChannels.end(), channel);
	
	if (found != this->joinedChannels.end())
		this->joinedChannels.erase(found);
}

void	IRC::User::appendBuffer(std::string str) { this->buffer.append(str); }
void	IRC::User::clearBuffer(void) { this->buffer.clear(); }

/* -- Member functions -- */
std::string		IRC::User::getJoinedChannelsString(void) const
{
	std::string channelsString = "";
	
	for (std::vector<IRC::Channel>::const_iterator channelIt = this->joinedChannels.begin(); channelIt != this->joinedChannels.end(); ++channelIt)
	{
		channelsString += channelIt->getName();
		if (channelIt + 1 != this->joinedChannels.end())
			channelsString += " ";
	}

	return channelsString;
}

bool			IRC::User::isInChannel(IRC::Channel channel) const
{
	if (std::find(this->joinedChannels.begin(), this->joinedChannels.end(), channel) != this->joinedChannels.end())
		return true;
	return false;
}

/* -- Non-member functions -- */
bool	IRC::operator== (const IRC::User lhs, const IRC::User rhs)
{
	if (lhs.getSocket() != rhs.getSocket())
		return false;
	return true;
}

std::vector<IRC::User>::iterator	IRC::findUser(std::vector<IRC::User>& users, std::string nick)
{
	std::vector<IRC::User>::iterator it;
	
	for (it = users.begin(); it != users.end(); it++)
	{
		std::cout << it->getNick();
		if (it->getNick().compare(nick) == 0)
			return it;
	}
	return it;
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
