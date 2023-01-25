/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:55:46 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/24 16:59:38 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace IRC
{
	class User
	{
	private:
		int socket;
		std::string password;
		std::string nick;
		std::string user;
		std::string realname;
		bool authenticated;

	public:
		User();
		User(int socket);
		User(const User& other);
		~User();
		User &operator=(const User &other);

		int getSocket(void) const;
		std::string getPassword(void) const;
		std::string getNick(void) const;
		std::string getUser(void) const;
		std::string getRealname(void) const;
		bool isAuthenticated(void) const;
		void setPassword(std::string password);
		void setNick(std::string nick);
		void setUser(std::string user);
		void setRealname(std::string realname);
		void changeAuthenticated();
	};
	bool 	operator== (const IRC::User lhs, const IRC::User rhs);
	int		findUser(std::vector<User> users, int event_fd);
	void	printUser(User user);
	void	printUsers(std::vector<User> users);
}
