/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:52:13 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/31 14:49:50 by karisti-         ###   ########.fr       */
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
			void						addUser(IRC::User& user, ChannelUserTypes userType);
			bool						existsUser(User user);
			void						removeUser(User user);
			std::string					getName() const;
			std::string					getUsersString(void);
			std::vector<User>			getOperators() const;
			std::vector<User>			getModerators() const;
			std::vector<User>			getUsers() const;
			std::string					getTopic() const;
			std::string					getPassword() const;
			void						setTopic(std::string newTopic);
			void						setName(std::string newName);
			bool						checkPassword(std::string pass) const;
			bool						isInviteOnly() const;
			void						setInviteOnly(bool newInviteOnlyMode);
			void						sendMessageToAll(std::string message);
			void						sendMessageToOperators(std::string message);
			void						sendMessageToModerators(std::string message);
			void						sendMessageToUsers(std::string message);
			void						broadcastAction(IRC::Server* server, IRC::User user, std::string command);
			bool						isOperator(IRC::User user);
			bool						isModerator(IRC::User user);
			bool						isUser(IRC::User user);
			bool						isEmpty(void);
	};
	bool	operator== (const Channel lhs, const Channel rhs);
	
	void	printChannels(std::vector<Channel>& channels);
	void	printChannel(Channel& channel);
}
