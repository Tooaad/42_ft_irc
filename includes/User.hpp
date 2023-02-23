/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:55:46 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/23 12:32:58 by karisti-         ###   ########.fr       */
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
			int						socket;
			std::string				password;
			std::string				nick;
			std::string				user;
			std::string				realname;
			std::string				hostname;
			std::string				servername;
			bool					authenticated;
			bool					invisible;
			bool					op;
			bool					subscribe;
			bool					pingReq;
			std::string				pingKey;
			time_t					timeout;
			std::vector<Channel>	joinedChannels;
			std::vector<User>		privateConvers;
			std::string				buffer;

		public:
			User();
			User(int socket);
			User(int socket, std::string hostname);
			User(const User& other);
			~User();
			User &operator=(const User &other);
			
			/* -- Getters -- */
			int						getSocket(void) const;
			std::string				getPassword(void) const;
			std::string				getNick(void) const;
			std::string				getUser(void) const;
			std::string				getRealname(void) const;
			std::string				getHostname(void) const;
			std::string				getServername(void) const;
			bool					isAuthenticated(void) const;
			bool					isInvisible(void) const;
			bool					isOp(void) const;
			bool					isSubscribed(void) const;
			bool					isPinged(void) const;
			std::string				getPingKey(void) const;
			time_t					getTimeout(void) const;
			std::vector<Channel>&	getJoinedChannels(void);
			std::vector<User>&		getPrivateConvers(void);
			std::string				getBuffer(void) const;
			
			/* -- Setters -- */
			void					setPassword(std::string password);
			void					setNick(std::string nick);
			void					setUser(std::string user);
			void					setRealname(std::string realname);
			void					setHostname(std::string realname);
			void					setServername(std::string realname);
			void					changeAuthenticated(void);
			void					changeInvisibility(void);
			void					deOp(void);
			void					changeSubscription(void);
			void					changeRequest(bool req);
			void					setPingKey(std::string key);
			void					setTimeout(time_t timeout);

			/* -- Modifiers -- */
			void					addJoinedChannel(Channel& channel);
			void					removeJoinedChannel(Channel channel);
			void					addPrivateConvers(User& user);
			void					removePrivateConvers(User user);
			void					appendBuffer(std::string str);
			void					clearBuffer(void);

			/* -- Member functions -- */
			std::string				getJoinedChannelsString(void) const;
			std::string				getPrivateConversString(void) const;
			bool					isInChannel(Channel channel) const;
			bool					isInPrivateConvers(User user) const;
			void					sendMessage(std::string message) const;
	};
	
	/* -- Non-member functions -- */
	bool								operator== (const User lhs, const User rhs);
	std::vector<IRC::User>::iterator	findUserFD(std::vector<IRC::User>& users, int fd);
	std::vector<IRC::User>::iterator	findUser(std::vector<User>& users, std::string nick);
	void								printUser(User user);
	void								printUsers(std::vector<User> users);
}
