/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:26 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/23 14:45:04 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

IRC::User::User(void) : socket(0), password(""), nick(""), user(""), authenticated(false)
{
}

IRC::User::User(int socket) : socket(socket), password(""), nick(""), user(""), authenticated(false)
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

void IRC::User::changeAuthenticated()
{
	this->authenticated = !authenticated;
}

int IRC::findUser(std::vector<IRC::User> users, int event_fd)
{
	std::vector<IRC::User>::iterator it = users.begin();
	int i = 0;
	for (; it != users.end(); it++, i++)
	{
		if ((*it).getSocket() == event_fd)
			return i;
	}
	return i;
}

void	IRC::printUsers(std::vector<IRC::User> users)
{
	std::vector<IRC::User>::iterator it = users.begin();
	for (; it != users.end(); it++)
		printUser(*it);
}

void	IRC::printUser(IRC::User user)
{
	std::cout << "User: " << user.getSocket() << " --> " << user.isAuthenticated() << ", Pass: " << user.getPassword() << ", User: " << user.getUser() << std::endl;
}


bool IRC::operator== (const IRC::User lhs, const IRC::User rhs) {
	if (lhs.getSocket() != rhs.getSocket())
		return false;
	return true;
}
