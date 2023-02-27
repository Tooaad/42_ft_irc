/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:26 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/27 10:50:48 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"


IRC::User::User(void)
{
	this->socket = 0;
	this->password = "";
	this->nick = "";
	this->user = "";
	this->realname = "";
	this->hostname =  "";
	this->servername = "";
	this->authenticated = false;
	this->invisible = false;
	this->op = false;
	this->subscribe = false;
	this->buffer = "";
	this->pingReq = false;
	this->timeout = time(NULL);
}

IRC::User::User(const IRC::User& other) { *this = other; }
IRC::User::~User() {}

IRC::User& IRC::User::operator=(const IRC::User &other)
{
	this->address = other.address;
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
	this->pingReq = other.pingReq;
	
	return *this;
}

/* -- Getters -- */
sockaddr_in					IRC::User::getAddress(void) const { return this->address; }
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
bool						IRC::User::isPinged(void) const { return this->pingReq; }
std::string					IRC::User::getPingKey(void) const { return this->pingKey; }
time_t						IRC::User::getTimeout(void) const { return this->timeout; }
std::vector<IRC::Channel>&	IRC::User::getJoinedChannels(void) { return this->joinedChannels; }
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
void						IRC::User::setPingKey(std::string key) { this->pingKey = key; }

/* -- Modifiers -- */
void	IRC::User::addJoinedChannel(IRC::Channel& channel)
{
	if (!this->isInChannel(channel))
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
void			IRC::User::startListeningSocket(int serverSocket)
{
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);
	
	socklen_t addressSize = sizeof(this->address);
	
	this->socket = accept(serverSocket, (struct sockaddr *)&this->address, &addressSize);
	if (this->socket == -1)
		perror("Accept socket error");

	if (getnameinfo((struct sockaddr *) &this->address, addressSize, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		std::cout << "Host1: " << host << " connected on port " << service << std::endl;
	else 
	{
		inet_ntop(AF_INET, &this->address.sin_addr, host, NI_MAXHOST);
		std::cout << "Host: " << host << " connected on port " << ntohs(this->address.sin_port) << std::endl;
	}
	
	std::string s(host);
	this->hostname = s;
}

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

void			IRC::User::sendMessage(std::string message) const
{
	message += "\r\n";
	send(getSocket(), message.c_str(), message.size(), 0);
}

/* -- Non-member functions -- */
bool	IRC::operator== (const IRC::User lhs, const IRC::User rhs)
{
	if (lhs.getSocket() != rhs.getSocket())
		return false;
	return true;
}

std::vector<IRC::User>::iterator	IRC::findUserFd(std::vector<IRC::User>& users, int fd)
{
	std::vector<IRC::User>::iterator it = users.begin();
	
	for (; it != users.end(); it++)
	{
		std::cout << it->getSocket();
		if (it->getSocket() == fd)
			return it;
	}
	return it;
}

std::vector<IRC::User>::iterator	IRC::findUser(std::vector<IRC::User>& users, std::string nick)
{
	std::vector<IRC::User>::iterator it = users.begin();
	
	for (; it != users.end(); it++)
	{
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

void	IRC::User::changeRequest(bool req)
{
	this->pingReq = req;
}
