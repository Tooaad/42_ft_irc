/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelTopic.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:29:32 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/30 18:32:32 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"
#include <algorithm>

namespace IRC
{
	class Server;
	class Command;

	class ChannelTopic : public Command
	{
		public:
			ChannelTopic();
			virtual ~ChannelTopic();

			void exec(IRC::Server* server, IRC::User& user);
	};
}