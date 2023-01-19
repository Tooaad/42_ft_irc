/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:26 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/19 20:02:18 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

IRC::User::User(void) : socket(0), password(""), nick(""), user(""), authenticated(false)
{
}

IRC::User::User(int socket) : socket(socket), password(""), nick(""), user(""), authenticated(false)
{
}

IRC::User::~User()
{
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

bool IRC::User::isAuthenticated(void) const
{
	return this->authenticated;
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

void IRC::User::setAuthenticated()
{
	this->authenticated = !authenticated;
}

IRC::User IRC::findUser(std::vector<IRC::User> users, int event_fd)
{
	for (std::vector<IRC::User>::iterator it = users.begin(); it != users.end(); it++)
	{
		if ((*it).getSocket() == event_fd)
			return *it;
	}
	return NULL;
}
