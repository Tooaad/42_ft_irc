/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:55:46 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/19 20:06:18 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

namespace IRC
{
	class User
	{
	private:
		int socket;
		std::string password;
		std::string nick;
		std::string user;
		bool authenticated;

	public:
		User();
		User(int socket);
		// User(const User& other);
		~User();
		User &operator=(const User &other);

		int getSocket(void) const;
		std::string getPassword(void) const;
		std::string getNick(void) const;
		std::string getUser(void) const;
		bool isAuthenticated(void) const;
		void setPassword(std::string password);
		void setNick(std::string nick);
		void setUser(std::string user);
		void setAuthenticated();
	};
	IRC::User findUser(std::vector<IRC::User> users, int event_fd);
}
