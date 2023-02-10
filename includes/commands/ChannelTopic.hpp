/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelTopic.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:29:32 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/10 16:34:49 by karisti-         ###   ########.fr       */
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

			void	exec(Server* server, User* user);
	};
}
