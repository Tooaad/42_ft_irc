/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 23:07:51 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/28 21:10:10 by gpernas-         ###   ########.fr       */
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