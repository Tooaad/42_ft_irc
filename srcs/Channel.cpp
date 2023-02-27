/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:51:40 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/27 17:41:04 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"


IRC::Channel::Channel()
{
	this->name = "";
	this->topic = "";
	this->password = "";
	this->inviteOnlyMode = false;
	this->secretMode = false;
	this->freeTopicMode = true;
	this->publicMsgMode = false;
	this->moderatedMode = false;
	this->maxUsers = 0;
}

IRC::Channel::Channel(std::string name)
{
	this->name = name;
	this->topic = "";
	this->password = "";
	this->inviteOnlyMode = false;
	this->secretMode = false;
	this->freeTopicMode = true;
	this->publicMsgMode = false;
	this->moderatedMode = false;
	this->maxUsers = 0;
}

IRC::Channel::Channel(std::string name, IRC::User createdBy, IRC::Server* server)
{
	this->name = name;
	this->topic = "";
	this->password = "";
	this->inviteOnlyMode = false;
	this->secretMode = false;
	this->freeTopicMode = true;
	this->publicMsgMode = false;
	this->moderatedMode = false;
	this->maxUsers = 0;
	
	addUser(createdBy);
	addOperator(createdBy, server);
}

IRC::Channel::Channel(const IRC::Channel &other) { *this = other; }
IRC::Channel::~Channel() {}

IRC::Channel &IRC::Channel::operator=(const IRC::Channel &other)
{
	if (this != &other)
	{
		this->name = other.name;
		this->topic = other.topic;
		this->password = other.password;
		this->operators = other.operators;
		this->moderators = other.moderators;
		this->users = other.users;
		this->inviteOnlyMode = other.inviteOnlyMode;
		this->secretMode = other.secretMode;
		this->freeTopicMode = other.freeTopicMode;
		this->publicMsgMode = other.publicMsgMode;
		this->moderatedMode = other.moderatedMode;
		this->maxUsers = other.maxUsers;
	}
	
	return *this;
}

/* -- Getters -- */
std::string					IRC::Channel::getName(void) const { return this->name; }
std::string					IRC::Channel::getTopic(void) const { return this->topic; }
std::string					IRC::Channel::getPassword(void) const { return this->password; }
std::vector<IRC::User>&		IRC::Channel::getOperators(void) { return this->operators; }
std::vector<IRC::User>&		IRC::Channel::getModerators(void) { return this->moderators; }
std::vector<IRC::User>&		IRC::Channel::getUsers(void) { return this->users; }
bool						IRC::Channel::isInviteOnly(void) const { return this->inviteOnlyMode; }
bool						IRC::Channel::isSecret(void) const { return this->secretMode; }
bool						IRC::Channel::isFreeTopic(void) const { return this->freeTopicMode; }
bool						IRC::Channel::isPublicMsg(void) const { return this->publicMsgMode; }
bool						IRC::Channel::isModerated(void) const { return this->moderatedMode; }
int							IRC::Channel::getMaxUsers(void) const { return this->maxUsers; }

/* -- Setters -- */
void						IRC::Channel::setName(std::string newName) { this->name = newName; }
void						IRC::Channel::setTopic(std::string newTopic) { this->topic = newTopic; }
void						IRC::Channel::setPassword(std::string password) { this->password = password; }
void						IRC::Channel::changeInviteOnly(void) { this->inviteOnlyMode = !this->inviteOnlyMode; }
void						IRC::Channel::changeSecrecy(void) { this->secretMode = !this->secretMode; }
void						IRC::Channel::changeFreeTopic(void) { this->freeTopicMode = !this->freeTopicMode; }
void						IRC::Channel::changePublicMsg(void) { this->publicMsgMode = !this->publicMsgMode; }
void						IRC::Channel::changeModerated(void) { this->moderatedMode = !this->moderatedMode; }
void						IRC::Channel::setMaxUsers(int size) { if (size < 0) { size = 0; } this->maxUsers = size; }

/* -- Modifiers -- */
void	IRC::Channel::addOperator(IRC::User user, IRC::Server* server)
{
	if (user == User())
		return ;
	
	if (!isOperator(user))
	{
		this->operators.push_back(user);
		server->updateUserInChannels(user);
	}
}

void	IRC::Channel::removeOperator(IRC::User user, IRC::Server* server)
{
	if (user == User())
		return ;
	
	std::vector<IRC::User>::iterator found = std::find(this->operators.begin(), this->operators.end(), user);
	if (found != this->operators.end())
	{
		this->operators.erase(found);
		server->updateUserInChannels(user);
	}
}

void	IRC::Channel::addModerator(IRC::User user, IRC::Server* server)
{
	if (user == User())
		return ;
	
	if (!isModerator(user))
	{
		this->moderators.push_back(user);
		server->updateUserInChannels(user);
	}
}

void	IRC::Channel::removeModerator(IRC::User user, IRC::Server* server)
{
	if (user == User())
		return ;
	
	std::vector<IRC::User>::iterator found = std::find(this->moderators.begin(), this->moderators.end(), user);
	if (found != this->moderators.end())
	{
		this->moderators.erase(found);
		server->updateUserInChannels(user);
	}
}

void	IRC::Channel::addUser(IRC::User& user)
{
	if (user == User())
		return ;
	
	if (!existsUser(user))
		this->users.push_back(user);
}

void	IRC::Channel::removeUser(IRC::Server* server, IRC::User& user)
{
	if (user == User())
		return ;
	
	std::vector<IRC::User>::iterator found = std::find(this->users.begin(), this->users.end(), user);
	if (found != this->users.end())
		this->users.erase(found);

	removeOperator(user, server);
	removeModerator(user, server);

	user.removeJoinedChannel(*this);
	
	if (isEmpty())
		server->removeChannel(*this);
}

/* -- Member functions -- */
bool	IRC::Channel::isOperator(IRC::User user) const
{
	if (std::find(this->operators.begin(), this->operators.end(), user) != this->operators.end())
		return true;
	return false;
}

bool	IRC::Channel::isModerator(IRC::User user) const
{
	if (std::find(this->moderators.begin(), this->moderators.end(), user) != this->moderators.end())
		return true;
	return false;
}

bool	IRC::Channel::existsUser(IRC::User user) const
{
	if (std::find(this->users.begin(), this->users.end(), user) != this->users.end())
		return true;
	return false;
}

std::string	IRC::Channel::getUsersString(void) const
{
	std::string usersString = "";

	for (std::vector<IRC::User>::const_iterator userIt = this->users.begin(); userIt != this->users.end(); userIt++)
	{
		if (usersString.size() > 0)
			usersString += " ";

		if (isOperator(*userIt))
			usersString += "@";
			
		if (isModerator(*userIt))
			usersString += "+";
	
		usersString += userIt->getNick();
	}

	return usersString;
}

std::string	IRC::Channel::getUsersStringVisible(void) const
{
	std::string usersString = "";

	for (std::vector<IRC::User>::const_iterator userIt = this->users.begin(); userIt != this->users.end(); userIt++)
	{
		if(userIt->isInvisible())
			continue ;

		if (usersString.size() > 0)
			usersString += " ";

		if (isOperator(*userIt))
			usersString += "@";
			
		if (isModerator(*userIt))
			usersString += "+";
	
		usersString += userIt->getNick();
	}

	return usersString;
}

bool	IRC::Channel::hasPassword(void) const 
{
	return this->password.size() > 0;
}

bool	IRC::Channel::checkPassword(std::string pass) const
{
	if (!hasPassword() || this->password.compare(pass) == 0)
		return true;
	return false;
}

bool	IRC::Channel::hasMax(void) const
{
	return this->maxUsers > 0;
}

bool	IRC::Channel::isFull(void) const
{
	if (hasMax() && (int)this->users.size() >= getMaxUsers())
		return true;
	return false;
}

bool	IRC::Channel::isEmpty(void) const
{
	if (this->users.empty())
		return true;
	return false;
}

void	IRC::Channel::sendMessageToUsers(IRC::User sender, std::string message)
{
	for (std::vector<IRC::User>::iterator it = this->users.begin(); it != this->users.end(); it++)
	{
		if (!(*it == sender))
			it->sendMessage(message);
	}
}

/* -- Non-member functions -- */
bool	IRC::operator== (const IRC::Channel lhs, const IRC::Channel rhs)
{
	if (lhs.getName().compare(rhs.getName()) == 0)
		return true;
	return false;
}

void	IRC::printChannels(std::vector<IRC::Channel>& channels)
{
	if (channels.size() == 0)
		return ;
	std::cout << "------- Channels -------" << std::endl;
	for (std::vector<IRC::Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
		printChannel(*it);
	std::cout << "------------------------" << std::endl;
}

void	IRC::printChannel(IRC::Channel& channel)
{	
	std::cout << channel.getName() << ":" << std::endl;
	std::cout << "	> Topic: " << channel.getTopic() << std::endl;
	std::cout << "	> Password: " << channel.getPassword() << std::endl;
	std::cout << "	> Mode: ";
	
	std::string modes = "";
	modes += (channel.isInviteOnly()) ? "+i" : "-i";
	modes += " ";
	modes += (channel.isSecret()) ? "+s" : "-s";
	modes += " ";
	modes += (channel.isFreeTopic()) ? "+t" : "-t";
	modes += " ";
	modes += (channel.isPublicMsg()) ? "+n" : "-n";
	modes += " ";
	modes += (channel.isModerated()) ? "+m" : "-m";
	modes += " ";
	
	std::cout << modes << std::endl;
	std::cout << "	> Max users: " << channel.getMaxUsers() << std::endl;
	std::cout << "	> Users: " << channel.getUsersString() << std::endl;
	std::cout << std::endl;
}
