/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelJoin.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:07:58 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/25 09:26:56 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"
#include <algorithm>

namespace IRC
{
	class Server;
	class Command;
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
			int		parseArgs(void);
			int		joinExistingChannel(IRC::Channel& channel, std::string nick);
			int		createNewChannel(std::string channelName, std::string nick, std::vector<IRC::Channel>& channels);
	};
}
