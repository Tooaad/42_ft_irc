/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 23:07:51 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/27 23:08:13 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"
#include <algorithm>

namespace IRC
{
	class Server;
	class Command;

	class PrivMsg : public Command
	{
		private:
			std::vector<std::string> channelsArray;

		public:
			PrivMsg();
			virtual ~PrivMsg();

			void exec(IRC::Server* server, IRC::User& user);

		private:
			int		parseArgs(void);
	};
}
