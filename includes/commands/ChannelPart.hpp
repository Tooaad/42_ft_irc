/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelPart.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:20:00 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/31 11:20:07 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"
#include <algorithm>

namespace IRC
{
	class Command;

	class ChannelPart : public Command
	{
		private:
			std::vector<std::string> channelsArray;

		public:
			ChannelPart();
			virtual ~ChannelPart();

			void exec(IRC::Server* server, IRC::User& user);

		private:
			int		parseArgs(void);
	};
}
