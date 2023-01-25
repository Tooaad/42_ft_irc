/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Username.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:51:15 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/24 13:54:16 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"

namespace IRC 
{
	class Server;
	class Command;
	class Username : public Command
	{
		public:
			Username();
			Username(Username const& other);
			virtual ~Username();

			void exec(IRC::Server* server, IRC::User& user);
	};
}

