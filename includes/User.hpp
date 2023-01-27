/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:55:46 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/27 19:58:19 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Channel.hpp"


namespace IRC
{
	class Channel;
	
	class User
	{
	private:
		int socket;
		std::string password;
		std::string nick;
		std::string user;
		std::string realname;
		std::string hostname;
		std::string servername;
		bool authenticated;
		std::vector<Channel> joinedChannels;

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
		std::string getHostname(void) const;
		std::string getServername(void) const;
		bool isAuthenticated(void) const;
		std::vector<Channel> getJoinedChannels(void) const;
		void addJoinedChannel(Channel channel);
		void removeJoinedChannel(Channel channel);
		std::string	getJoinedChannelsString(void);
		void setPassword(std::string password);
		void setNick(std::string nick);
		void setUser(std::string user);
		void setRealname(std::string realname);
		void setHostname(std::string realname);
		void setServername(std::string realname);
		void changeAuthenticated();
	};
	bool 	operator== (const User lhs, const User rhs);
	int		findUser(std::vector<User> users, int event_fd);
	void	printUser(User user);
	void	printUsers(std::vector<User> users);
}
