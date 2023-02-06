/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 02:14:55 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/06 17:55:04 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"

namespace IRC 
{
	class Server;
	class Command;
	class Ping : public Command
	{
		public:
			Ping();
			virtual ~Ping();

			void exec(IRC::Server* server, IRC::User& user);
	};
}

