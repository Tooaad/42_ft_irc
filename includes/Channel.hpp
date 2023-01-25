/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:52:13 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/25 20:34:51 by karisti-         ###   ########.fr       */
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
			void						addUser(std::string user);
			bool						existUser(std::string user);
			void						removeUser(std::string user);
			std::vector<std::string>	getUsers() const;
			std::string					getCreatedBy() const;
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
