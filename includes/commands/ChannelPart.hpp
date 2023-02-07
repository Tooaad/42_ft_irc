/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelPart.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:20:00 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/07 12:00:52 by karisti-         ###   ########.fr       */
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
			ChannelPart(const ChannelPart& other);
			virtual ~ChannelPart();
			ChannelPart& operator=(const ChannelPart& other);

			void	exec(IRC::Server* server, IRC::User& user);

		private:
			int		parseArgs(IRC::Server server, IRC::User user);
	};
}
