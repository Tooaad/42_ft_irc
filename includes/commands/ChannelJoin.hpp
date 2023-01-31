/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelJoin.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:07:58 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/31 14:28:55 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"
#include <algorithm>

#define MAX_CHANNELS 3

namespace IRC
{
	class Command;
	class Server;

	class ChannelJoin : public Command
	{
		private:
			std::vector<std::string> channelsArray;
			std::vector<std::string> passwordsArray;

		public:
			ChannelJoin();
			virtual ~ChannelJoin();

			void exec(IRC::Server* server, IRC::User& user);

		private:
			int				parseArgs(void);
			IRC::Channel*	joinExistingChannel(IRC::Channel& channel, IRC::User &user);
			IRC::Channel*	createNewChannel(std::string channelName, IRC::User& user, IRC::Server* server);
	};
}
