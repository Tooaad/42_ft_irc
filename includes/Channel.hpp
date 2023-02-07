/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:52:13 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/07 11:36:15 by karisti-         ###   ########.fr       */
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
			std::string				getName() const;
			std::vector<User>		getOperators() const;
			std::vector<User>		getModerators() const;
			std::vector<User>		getUsers() const;
			std::string				getTopic() const;
			std::string				getPassword() const;
			bool					isInviteOnly() const;
			bool					isSecret() const;
			bool					isFreeTopic() const;
			bool					isPublicMsg() const;
			bool					isModerated() const;
			int						getMaxUsers(void);

			/* -- Setters -- */
			void					setName(std::string newName);
			void					setTopic(std::string newTopic);
			void					setPassword(std::string password);
			void					changeInviteOnly();
			void					changeSecrecy();
			void					changeFreeTopic();
			void					changePublicMsg();
			void					changeModerated();
			void					setMaxUsers(int size);
			
			/* -- Modifiers -- */
			void					addOperator(IRC::User user);
			void					removeOperator(IRC::User user);
			void					addModerator(IRC::User user);
			void					removeModerator(IRC::User user);
			void					addUser(User& user);
			void					removeUser(User user);

			/* -- Member functions */
			bool					isOperator(IRC::User user);
			bool					isModerator(IRC::User user);
			bool					existsUser(User user);
			std::string				getUsersString(void);
			bool					hasPassword(void) const;
			bool					checkPassword(std::string pass) const;
			bool					hasMax(void) const;
			bool					isFull(void) const;
			bool					isEmpty(void);
			void					sendMessageToOperators(std::string message);
			void					sendMessageToModerators(std::string message);
			void					sendMessageToUsers(std::string message);
			void					broadcastAction(IRC::Server* server, IRC::User user, std::string command);
	};

	/* -- Non-member functions */
	bool	operator== (const Channel lhs, const Channel rhs);
	void	printChannels(std::vector<Channel>& channels);
	void	printChannel(Channel& channel);
}
