/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:51:40 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/30 20:10:57 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

IRC::Channel::Channel() {}
IRC::Channel::Channel(std::string name, IRC::User createdBy) : name(name), topic(""), inviteOnlyMode(false), maxUsers(0)
{
	operators.push_back(createdBy);
}

IRC::Channel::Channel(const IRC::Channel &other) { *this = other; }
IRC::Channel::~Channel() {}

IRC::Channel &IRC::Channel::operator=(const IRC::Channel &other)
{
	if (this != &other)
	{
		name = other.name;
		users = other.users;
		operators = other.operators;
		topic = other.topic;
		password = other.password;
		inviteOnlyMode = other.inviteOnlyMode;
	}
	return *this;
}

std::string					IRC::Channel::getName() const { return name; }
void						IRC::Channel::setName(std::string newName) { name = newName; }
void						IRC::Channel::setMaxUsers(size_t size) { maxUsers = size; }
size_t						IRC::Channel::getMaxUsers(void) { return maxUsers; }
std::vector<IRC::User>		IRC::Channel::getUsers() const { return users; }
void						IRC::Channel::addUser(IRC::User user) { users.push_back(user); }
std::vector<IRC::User>		IRC::Channel::getOperators() const { return operators; }
std::string					IRC::Channel::getTopic() const { return topic; }
void						IRC::Channel::setTopic(std::string newTopic) { topic = newTopic; }
std::string					IRC::Channel::getPassword() const { return password; }
bool						IRC::Channel::isInviteOnly() const { return inviteOnlyMode; }
void						IRC::Channel::setInviteOnly(bool newInviteOnlyMode) { inviteOnlyMode = newInviteOnlyMode; }


bool	IRC::Channel::checkPassword(std::string pass) const
{
	if (password.size() == 0 || password.compare(pass) == 0)
		return true;
	return false;
}

bool	IRC::Channel::existsUser(IRC::User user)
{
	std::vector<IRC::User>::iterator found = std::find(users.begin(), users.end(), user);
	
	if (found != users.end())
		return true;
	return false;
}

void	IRC::Channel::removeUser(IRC::User user)
{
	std::vector<IRC::User>::iterator found = std::find(users.begin(), users.end(), user);
	
	if (found != users.end())
		users.erase(found);
}

std::string	IRC::Channel::getUsersString(void)
{
	std::string usersString = "";
	
	for (std::vector<IRC::User>::const_iterator user_it = users.begin(); user_it != users.end(); ++user_it)
	{
		usersString += user_it->getNick();
		if (user_it + 1 != users.end())
			usersString += " ";
	}
	
	return usersString;
}

std::string	IRC::Channel::getOperatorsString(void)
{
	std::string operatorsString = "";
	
	for (std::vector<IRC::User>::const_iterator operator_it = operators.begin(); operator_it != operators.end(); ++operator_it)
	{
		operatorsString += operator_it->getNick();
		if (operator_it + 1 != operators.end())
			operatorsString += " ";
	}
	
	return operatorsString;
}

void	IRC::Channel::sendMessage(std::string message)
{
	for (std::vector<IRC::User>::iterator it = users.begin(); it != users.end(); it++)
		send(it->getSocket(), message.c_str(), message.size(), 0);
}

bool	IRC::Channel::isFull(void) const
{
	if (maxUsers > 0 && users.size() >= maxUsers)
		return true;
	return false;
}

bool	IRC::operator== (const IRC::Channel lhs, const IRC::Channel rhs)
{
	if (lhs.getName().compare(rhs.getName()) == 0)
		return true;
	return false;
}

void	IRC::printChannel(IRC::Channel& channel)
{
	std::cout << "Channel name: " << channel.getName();
	std::cout << ", Operators: " << channel.getOperatorsString();
	std::cout << ", Topic: " << channel.getTopic();
	std::cout << ", Password: " << channel.getPassword();
	std::cout << ", Invite Only mode: " << channel.isInviteOnly();
	std::cout << ", Max users: " << channel.getMaxUsers();
	std::cout << std::endl;
	
	std::cout << "Users: " << channel.getUsersString() << std::endl;
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



