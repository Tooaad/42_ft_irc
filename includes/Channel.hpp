/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:52:13 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/30 20:35:56 by gpernas-         ###   ########.fr       */
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
			std::string					getName() const;
			std::vector<User>			getUsers() const;
			std::string					getUsersString(void);
			std::vector<User>			getOperators() const;
			std::string					getOperatorsString(void);
			std::string					getTopic() const;
			std::string					getPassword() const;
			void						setTopic(std::string newTopic);
			void						setName(std::string newName);
			bool						checkPassword(std::string pass) const;
			bool						isInviteOnly() const;
			void						setInviteOnly(bool newInviteOnlyMode);
			void						sendMessage(std::string message);
			
	};
	bool	operator== (const Channel lhs, const Channel rhs);
	
	void	printChannels(std::vector<Channel>& channels);
	void	printChannel(Channel& channel);
}
