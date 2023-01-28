/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:26 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/28 13:46:24 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

IRC::User::User(void) : socket(0), password(""), nick(""), user(""), realname(""), authenticated(false)
{
}

IRC::User::User(int socket) : socket(socket), password(""), nick(""), user(""), realname(""), authenticated(false)
{
}

IRC::User::User(const IRC::User& other)
{
	*this = other;
}

IRC::User::~User()
{
}

IRC::User& IRC::User::operator=(const IRC::User &other)
{
	this->authenticated = other.isAuthenticated();
	this->nick = other.getNick();
	this->password = other.getPassword();
	this->user = other.getUser();
	this->socket = other.getSocket();
	this->realname = other.getRealname();
	this->hostname = other.getHostname();
	this->servername = other.getServername();
	this->joinedChannels = other.getJoinedChannels();
	
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

bool IRC::User::isAuthenticated(void) const
{
	return this->authenticated;
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

void IRC::User::changeAuthenticated()
{
	this->authenticated = !authenticated;
}

void IRC::User::addJoinedChannel(IRC::Channel channel)
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

bool IRC::operator== (const IRC::User lhs, const IRC::User rhs) {
	if (lhs.getSocket() != rhs.getSocket())
		return false;
	return true;
}

IRC::User* IRC::findUser(std::vector<IRC::User> users, std::string nick)
{
	std::vector<IRC::User>::iterator it = users.begin();
	int i = 0;
	for (; it != users.end(); it++, i++)
	{
		if ((*it).getNick() == nick)
			return it.base();
	}
	return NULL;
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
