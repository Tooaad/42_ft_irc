/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:51:40 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/24 10:45:08 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

IRC::Channel::Channel() {}
IRC::Channel::Channel(std::string name) : name(name) {}
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

std::string IRC::Channel::getName() const
{
	return name;
}

void IRC::Channel::addUser(std::string user)
{
	users.push_back(user);
}

void IRC::Channel::removeUser(std::string user)
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

std::vector<std::string> IRC::Channel::getUsers() const
{
	return users;
}

void	printChannels(const std::vector<IRC::Channel>& channels)
{
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
}
