/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:51:40 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/26 21:10:27 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

IRC::Channel::Channel() {}
IRC::Channel::Channel(std::string name, std::string createdBy) : name(name), createdBy(createdBy), inviteOnlyMode(false) {}
IRC::Channel::Channel(const IRC::Channel &other) { *this = other; }
IRC::Channel::~Channel() {}

IRC::Channel &IRC::Channel::operator=(const IRC::Channel &other)
{
	if (this != &other)
	{
		name = other.name;
		users = other.users;
		createdBy = other.createdBy;
		topic = other.topic;
		password = other.password;
		inviteOnlyMode = other.inviteOnlyMode;
	}
	return *this;
}

std::string					IRC::Channel::getName() const { return name; }
void						IRC::Channel::setName(std::string newName) { name = newName; }
std::vector<std::string>	IRC::Channel::getUsers() const { return users; }
void						IRC::Channel::addUser(std::string user) { users.push_back(user); }
std::string					IRC::Channel::getCreatedBy() const { return createdBy; }
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

bool	IRC::Channel::existsUser(std::string user)
{
	std::vector<std::string>::iterator found = std::find(users.begin(), users.end(), user);
	
	if (found != users.end())
		return true;
	return false;
}

void	IRC::Channel::removeUser(std::string user)
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i] == user)
		{
			users.erase(users.begin() + i);
			break;
		}
	}
}

std::string	IRC::Channel::getUsersString(void)
{
	std::string usersString = "";
	for (std::vector<std::string>::const_iterator user_it = users.begin(); user_it != users.end(); ++user_it)
	{
		usersString += *user_it;
		if (user_it + 1 != users.end())
			usersString += " ";
	}
	
	return usersString;
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
	std::cout << ", Created By: " << channel.getCreatedBy();
	std::cout << ", Topic: " << channel.getTopic();
	std::cout << ", Password: " << channel.getPassword();
	std::cout << ", Invite Only mode: " << channel.isInviteOnly();
	std::cout << std::endl;
	
	const std::vector<std::string>& users = channel.getUsers();
	std::cout << "Users: ";
	for (std::vector<std::string>::const_iterator user_it = users.begin(); user_it != users.end(); ++user_it)
	{
		std::cout << *user_it;
		if (user_it + 1 != users.end())
			std::cout << ", ";
	}
	std::cout << std::endl;
	
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



