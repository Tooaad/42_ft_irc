/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 23:07:51 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/07 12:01:20 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"


namespace IRC
{
	class Server;
	class Command;

	class PrivMsg : public Command
	{
		public:
			PrivMsg();
			virtual ~PrivMsg();

			void exec(IRC::Server* server, IRC::User& user);
	};
}
