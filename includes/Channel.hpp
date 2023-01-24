/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:52:13 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/24 10:37:12 by karisti-         ###   ########.fr       */
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

		public:
			Channel();
			Channel(std::string name);
			Channel(const Channel& other);
			~Channel();
			Channel& operator=(const Channel& other);

			std::string					getName() const;
			void						addUser(std::string user);
			void						removeUser(std::string user);
			std::vector<std::string>	getUsers() const;
	};
	void	printChannels(const std::vector<Channel>& channels);
}
