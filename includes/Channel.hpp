/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:52:13 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/24 17:36:36 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace IRC
{
	class Channel
	{
		private:
			std::string					name;
			std::vector<std::string>	users;
			std::string					createdBy;
			
			std::string					topic;
			std::string					password;
			bool						inviteOnlyMode;
			

		public:
			Channel();
			Channel(std::string name, std::string createdBy);
			Channel(const Channel& other);
			~Channel();
			Channel& operator=(const Channel& other);

			std::string					getName() const;
			void						setName(std::string newName);
			std::string					getTopic() const;
			void						setTopic(std::string newTopic);
			bool						checkPassword(std::string pass) const;
			bool						isInviteOnly() const;
			void						setInviteOnly(bool newInviteOnlyMode);
			void						addUser(std::string user);
			void						removeUser(std::string user);
			std::vector<std::string>	getUsers() const;
	};
	bool	operator== (const IRC::Channel lhs, const IRC::Channel rhs);
	
	void	printChannels(const std::vector<Channel>& channels);
}
