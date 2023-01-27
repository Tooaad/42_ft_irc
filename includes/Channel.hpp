/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:52:13 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/27 17:41:29 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "User.hpp"

namespace IRC
{
	class Channel
	{
		private:
			std::string					name;
			std::vector<IRC::User>		users;
			IRC::User					createdBy;
			
			std::string					topic;
			std::string					password;
			bool						inviteOnlyMode;
			

		public:
			Channel();
			Channel(std::string name, User createdBy);
			Channel(const Channel& other);
			~Channel();
			Channel& operator=(const Channel& other);

			std::string					getName() const;
			void						setName(std::string newName);
			void						addUser(User user);
			bool						existsUser(User user);
			void						removeUser(User user);
			std::vector<IRC::User>		getUsers() const;
			std::string					getUsersString(void);
			IRC::User					getCreatedBy() const;
			std::string					getTopic() const;
			void						setTopic(std::string newTopic);
			std::string					getPassword() const;
			bool						checkPassword(std::string pass) const;
			bool						isInviteOnly() const;
			void						setInviteOnly(bool newInviteOnlyMode);
			
	};
	bool	operator== (const IRC::Channel lhs, const IRC::Channel rhs);
	
	void	printChannels(std::vector<Channel>& channels);
	void	printChannel(Channel& channel);
}
