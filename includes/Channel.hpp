/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:52:13 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/17 17:18:10 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sys/socket.h>
#include "User.hpp"
#include "Server.hpp"


namespace IRC
{
	class Server;
	class User;

	class Channel
	{
		public:
			enum ChannelUserTypes {
				NORMAL_USER,
				MODERATOR_USER,
				OPERATOR_USER
			};
		
		private:
			std::string				name;
			std::vector<User>		operators;
			std::vector<User>		moderators;
			std::vector<User>		users;
			std::string				topic;
			std::string				password;
			bool					inviteOnlyMode;
			bool					secretMode;
			bool					freeTopicMode;
			bool					publicMsgMode;
			bool					moderatedMode;
			int						maxUsers;

		public:
			Channel();
			Channel(std::string name, User createdBy);
			Channel(const Channel& other);
			~Channel();
			Channel& operator=(const Channel& other);

			/* -- Getters -- */
			std::string				getName(void) const;
			std::vector<User>&		getOperators(void);
			std::vector<User>&		getModerators(void);
			std::vector<User>&		getUsers(void);
			std::string				getTopic(void) const;
			std::string				getPassword(void) const;
			bool					isInviteOnly(void) const;
			bool					isSecret(void) const;
			bool					isFreeTopic(void) const;
			bool					isPublicMsg(void) const;
			bool					isModerated(void) const;
			int						getMaxUsers(void) const;

			/* -- Setters -- */
			void					setName(std::string newName);
			void					setTopic(std::string newTopic);
			void					setPassword(std::string password);
			void					changeInviteOnly(void);
			void					changeSecrecy(void);
			void					changeFreeTopic(void);
			void					changePublicMsg(void);
			void					changeModerated(void);
			void					setMaxUsers(int size);
			
			/* -- Modifiers -- */
			void					addOperator(IRC::User user);
			void					removeOperator(IRC::User user);
			void					addModerator(IRC::User user);
			void					removeModerator(IRC::User user);
			void					addUser(User& user);
			void					removeUser(Server& server, User& user);

			/* -- Member functions -- */
			bool					isOperator(IRC::User user) const;
			bool					isModerator(IRC::User user) const;
			bool					existsUser(User user) const;
			std::string				getUsersString(void) const;
			bool					hasPassword(void) const;
			bool					checkPassword(std::string pass) const;
			bool					hasMax(void) const;
			bool					isFull(void) const;
			bool					isEmpty(void) const;
			void					sendMessageToOperators(std::string message);
			void					sendMessageToModerators(std::string message);
			void					sendMessageToUsers(User sender, std::string message);
	};

	/* -- Non-member functions -- */
	bool	operator== (const Channel lhs, const Channel rhs);
	void	printChannels(std::vector<Channel>& channels);
	void	printChannel(Channel& channel);
}
