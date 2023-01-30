/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:52:13 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/30 19:17:38 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sys/socket.h>
#include "User.hpp"

namespace IRC
{
	class User;
	
	class Channel
	{
		private:
			std::string					name;
			std::vector<User>			users;
			std::vector<User>			operators;
			
			std::string					topic;
			std::string					password;
			bool						inviteOnlyMode;
			size_t						maxUsers;

		public:
			Channel();
			Channel(std::string name, User createdBy);
			Channel(const Channel& other);
			~Channel();
			Channel& operator=(const Channel& other);

			std::string					getName() const;
			void						setName(std::string newName);
			void						setMaxUsers(size_t size);
			size_t						getMaxUsers(void);
			bool						isFull(void) const;
			void						addUser(User user);
			bool						existsUser(User user);
			void						removeUser(User user);
			std::vector<User>			getUsers() const;
			std::string					getUsersString(void);
			std::vector<User>			getOperators() const;
			std::string					getOperatorsString(void);
			std::string					getTopic() const;
			void						setTopic(std::string newTopic);
			std::string					getPassword() const;
			bool						checkPassword(std::string pass) const;
			bool						isInviteOnly() const;
			void						setInviteOnly(bool newInviteOnlyMode);
			void						sendMessage(std::string message);
			
	};
	bool	operator== (const Channel lhs, const Channel rhs);
	
	void	printChannels(std::vector<Channel>& channels);
	void	printChannel(Channel& channel);
}
