/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:52:13 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/31 18:23:56 by karisti-         ###   ########.fr       */
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
			std::string					name;
			std::vector<User>			operators;
			std::vector<User>			moderators;
			std::vector<User>			users;
			std::string					topic;
			
			std::string					password;
			bool						inviteOnlyMode;
			bool						secretMode;
			bool						freeTopicMode;
			bool						publicMsgMode;
			bool						moderatedMode;
			int							maxUsers;

		public:
			Channel();
			Channel(std::string name, User createdBy);
			Channel(const Channel& other);
			~Channel();
			Channel& operator=(const Channel& other);

			void						setMaxUsers(int size);
			int							getMaxUsers(void);
			bool						isFull(void) const;
			void						addUser(User& user);
			bool						existsUser(User user);
			void						removeUser(User user);
			std::string					getName() const;
			std::string					getUsersString(void);
			std::vector<User>			getOperators() const;
			void						addOperator(IRC::User user);
			void						removeOperator(IRC::User user);
			std::vector<User>			getModerators() const;
			void						addModerator(IRC::User user);
			void						removeModerator(IRC::User user);
			bool						isSecret() const;
			void						changeSecrecy();
			bool						isFreeTopic() const;
			void						changeFreeTopic();
			bool						isPublicMsg() const;
			void						changePublicMsg();
			bool						isModerated() const;
			void						changeModerated();
			std::vector<User>			getUsers() const;
			std::string					getTopic() const;
			std::string					getPassword() const;
			void						setPassword(std::string password);
			void						setTopic(std::string newTopic);
			void						setName(std::string newName);
			bool						checkPassword(std::string pass) const;
			bool						isInviteOnly() const;
			void						changeInviteOnly();
			void						sendMessageToOperators(std::string message);
			void						sendMessageToModerators(std::string message);
			void						sendMessageToUsers(std::string message);
			void						broadcastAction(IRC::Server* server, IRC::User user, std::string command);
			bool						isOperator(IRC::User user);
			bool						isModerator(IRC::User user);
			bool						isEmpty(void);
	};
	bool	operator== (const Channel lhs, const Channel rhs);
	
	void	printChannels(std::vector<Channel>& channels);
	void	printChannel(Channel& channel);
}
