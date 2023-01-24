/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:14:35 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/24 10:40:06 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <algorithm>
#include <typeinfo>
#include <map>
#include "Server.hpp"
#include "User.hpp"

namespace IRC
{
	class Server;
	class Command
	{
		enum Err {HAZLO, KEPA};
		
		private:
			std::map<std::string, Command*> cmd_map;

		public:

			Command();
			Command(std::string str);
			Command(const Command& other);
			Command& operator=(const Command& other);
			virtual ~Command();

			Command* find(std::string key) const;
			void detectCommand(IRC::Server* server, IRC::User& user);
			virtual void exec(IRC::Server* server, IRC::User& user);

		protected:

			std::string		command;
			int				id;
			std::string		args;
			int				argc;
			
			std::string		res;
			std::string		error;
			int				errn;
			
	};
}

