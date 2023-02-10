/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:00:31 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/10 16:34:49 by karisti-         ###   ########.fr       */
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
			virtual ~Mode();

			void	exec(Server* server, User* user);
		
		private:
			std::string		printChannelMax(IRC::Channel recept);
			std::string		printPassword(IRC::Channel recept);
	};
}
