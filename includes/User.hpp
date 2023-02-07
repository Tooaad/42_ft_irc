/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:55:46 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/07 13:38:31 by karisti-         ###   ########.fr       */
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
			time_t					timeout;
			std::vector<Channel>	joinedChannels;
			std::string				buffer;

		public:
			User();
			User(int socket);
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
			time_t					getTimeout(void) const;
			std::vector<Channel>	getJoinedChannels(void) const;
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
			void					deOp(void); // TOTO: Nombre funcion??
			void					changeSubscription(void);
			void					setTimeout(time_t timeout);

			/* -- Modifiers -- */
			void					addJoinedChannel(Channel& channel);
			void					removeJoinedChannel(Channel channel);
			void					appendBuffer(std::string str);
			void					clearBuffer(void);

			/* -- Member functions -- */
			std::string				getJoinedChannelsString(void) const;
			bool					isInChannel(Channel channel) const;
	};
	
	/* -- Non-member functions -- */
	bool								operator== (const User lhs, const User rhs);
	std::vector<IRC::User>::iterator	findUser(std::vector<User>& users, std::string nick);
	void								printUser(User user);
	void								printUsers(std::vector<User> users);
}
