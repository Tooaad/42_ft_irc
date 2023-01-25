/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:51:40 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/25 15:20:52 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

IRC::Channel::Channel() {}
IRC::Channel::Channel(std::string name, std::string createdBy) : name(name), createdBy(createdBy) {}
IRC::Channel::Channel(const IRC::Channel &other) : name(other.name), users(other.users) {}
IRC::Channel::~Channel() {}

IRC::Channel &IRC::Channel::operator=(const IRC::Channel &other)
{
	if (this != &other)
	{
		name = other.name;
		users = other.users;
	}
	return *this;
}

std::string					IRC::Channel::getName() const { return name; }
void						IRC::Channel::setName(std::string newName) { name = newName; }
std::string					IRC::Channel::getTopic() const { return topic; }
void						IRC::Channel::setTopic(std::string newTopic) { topic = newTopic; }
std::vector<std::string>	IRC::Channel::getUsers() const { return users; }
void						IRC::Channel::addUser(std::string user) { users.push_back(user); }
bool						IRC::Channel::isInviteOnly() const { return inviteOnlyMode; }
void						IRC::Channel::setInviteOnly(bool newInviteOnlyMode) { inviteOnlyMode = newInviteOnlyMode; }


bool	IRC::Channel::checkPassword(std::string pass) const
{
	if (password.size() == 0 || password.compare(pass) == 0)
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

bool	IRC::operator== (const IRC::Channel lhs, const IRC::Channel rhs)
{
	if (lhs.getName().compare(rhs.getName()) == 0)
		return true;
	return false;
}

void	IRC::printChannels(const std::vector<IRC::Channel>& channels)
{
	if (channels.size() == 0)
		return ;
	std::cout << "------- Channels -------" << std::endl;
	for (std::vector<IRC::Channel>::const_iterator it = channels.begin(); it != channels.end(); ++it)
	{
		std::cout << it->getName() << ": ";
		const std::vector<std::string>& users = it->getUsers();
		for (std::vector<std::string>::const_iterator user_it = users.begin(); user_it != users.end(); ++user_it)
		{
			std::cout << *user_it;
			if (user_it + 1 != it->getUsers().end())
				std::cout << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << "------------------------" << std::endl;
}
