/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:00:31 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/01 13:12:40 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"
#include "../Channel.hpp"
#include <sstream>

namespace IRC 
{
	class Server;
	class Command;
	class Mode : public Command
	{
		public:
			Mode();
			Mode(Mode const& other);
			virtual ~Mode();

			void exec(IRC::Server* server, IRC::User& user);
			std::string printChannelMax(IRC::Channel recept);
			std::string printPass(IRC::Channel recept);
	};
}

