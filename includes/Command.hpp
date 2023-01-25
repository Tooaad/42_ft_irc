/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:14:35 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/25 11:01:01 by karisti-         ###   ########.fr       */
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
		enum Errors {
			ERR_NOTREGISTERED=451,
			ERR_BADCHANMASK=476,
			ERR_NEEDMOREPARAMS=461,
			ERR_INVITEONLYCHAN=473,
			ERR_BADCHANNELKEY=475
		};
		
		private:
			static std::map<std::string, Command*> cmd_map;

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

