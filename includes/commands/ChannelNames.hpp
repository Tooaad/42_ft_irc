/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelNames.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:10:06 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/06 18:15:16 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"

namespace IRC
{
	class Command;

	class ChannelNames : public Command
	{
		private:
			std::vector<Channel> channelsArray;

		public:
			ChannelNames();
			ChannelNames(const ChannelNames& other);
			virtual ~ChannelNames();
			ChannelNames& operator=(const ChannelNames& other);

			void exec(Server* server, User& user);

		private:
			void	parseArgs(Server* server);
			void	printNames(User user, std::vector<Channel>::iterator itBegin, std::vector<Channel>::iterator itEnd);
	};
}
