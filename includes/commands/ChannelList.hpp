/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:46:06 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/28 12:16:13 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"
#include <sstream>


namespace IRC
{
	class ChannelList : public Command
	{
		public:
			ChannelList();
			virtual ~ChannelList();

			void	exec(Server* server, User& user);

		private:
			void	printList(Server server, User user, std::vector<Channel>::iterator itBegin, std::vector<Channel>::iterator itEnd);
	};
}
