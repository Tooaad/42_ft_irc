/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:14:35 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/25 15:24:05 by karisti-         ###   ########.fr       */
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
		public:
			enum ErrorNos {
				ERR_NOTREGISTERED=451,
				ERR_BADCHANMASK=476,
				ERR_NEEDMOREPARAMS=461,
				ERR_INVITEONLYCHAN=473,
				ERR_BADCHANNELKEY=475
			};
		
		protected:

			std::string		command;
			std::string		args;
			std::string		resMsg;
			int				errorNo;
			std::string		errorMsg;
			
			//int				id;
			//int				argc;
		
		private:
			static	std::map<std::string, Command*> cmd_map;


		public:
			Command();
			Command(std::string str);
			Command(const Command& other);
			Command& operator=(const Command& other);
			virtual ~Command();

			Command*		find(std::string key) const;
			void			detectCommand(IRC::Server* server, IRC::User& user);
			virtual void	exec(IRC::Server* server, IRC::User& user);
			void			answer(IRC::User& user);
			void			setError(ErrorNos errorNo, int n, ...);
			
		private:
			std::string		expandError(int argCount, va_list vaList, std::string errorStr);
	};
}
