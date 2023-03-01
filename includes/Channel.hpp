/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:52:13 by karisti-          #+#    #+#             */
/*   Updated: 2023/03/01 12:48:53 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "User.hpp"
#include "Server.hpp"


namespace IRC
{
	class Server;
	class User;

	class Channel
	{
		private:
			std::string				name;
			std::string				topic;
			std::string				password;
			std::vector<User>		operators;
			std::vector<User>		moderators;
			std::vector<User>		users;
			bool					inviteOnlyMode;
			bool					secretMode;
			bool					freeTopicMode;
			bool					publicMsgMode;
			bool					moderatedMode;
			int						maxUsers;

		public:
			Channel();
			Channel(std::string name);
			Channel(std::string name, User createdBy);
			Channel(const Channel& other);
			~Channel();
			Channel& operator=(const Channel& other);

			/* -- Getters -- */
			std::string				getName(void) const;
			std::string				getTopic(void) const;
			std::string				getPassword(void) const;
			std::vector<User>&		getOperators(void);
			std::vector<User>&		getModerators(void);
			std::vector<User>&		getUsers(void);
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
			void					addOperator(User user, Server* server);
			void					removeOperator(User user, Server* server);
			void					addModerator(User user, Server* server);
			void					removeModerator(User user, Server* server);
			bool					addUser(User& user);
			void					removeUser(Server* server, User& user);

			/* -- Member functions -- */
			bool					isOperator(User user) const;
			bool					isModerator(User user) const;
			bool					existsUser(User user) const;
			std::string				getUsersString(void) const;
			std::string				getUsersStringVisible(void) const;
			bool					hasPassword(void) const;
			bool					checkPassword(std::string pass) const;
			bool					hasMax(void) const;
			bool					isFull(void) const;
			bool					isEmpty(void) const;
			void					sendMessageToUsers(User sender, std::string message);
	};

	/* -- Non-member functions -- */
	bool	operator== (const Channel lhs, const Channel rhs);
	void	printChannels(std::map<std::string, Channel>& channels);
	void	printChannel(Channel& channel);
}
