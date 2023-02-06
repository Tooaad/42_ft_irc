/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:46:06 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/04 11:48:45 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"
#include <sstream>

namespace IRC
{
	class Command;

	class ChannelList : public Command
	{
		private:
			std::vector<Channel> channelsArray;

		public:
			ChannelList();
			virtual ~ChannelList();

			void exec(Server* server, User& user);

		private:
			void	parseArgs(Server* server);
			void	printNames(User user, std::vector<Channel>::iterator itBegin, std::vector<Channel>::iterator itEnd);
	};
}
