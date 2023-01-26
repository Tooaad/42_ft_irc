/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:14:35 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/26 20:27:31 by karisti-         ###   ########.fr       */
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
				ERR_BADCHANNELKEY=475,
				ERR_NOSUCHCHANNEL=403,
				ERR_NOTONCHANNEL=442,
				ERR_NONICKNAMEGIVEN=431,
				ERR_ERRONEUSNICKNAME=432,
				ERR_NICKNAMEINUSE=433
			};

			enum ReplyNos {
				TEST=451,
			};

			
		
		protected:

			std::string		command;
			std::string		args;
			int				replyNo;
			std::string		replyMsg;
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
			void			setReply(ReplyNos replyNo, int n, ...);
			
		private:
			std::string		expandMessage(int argCount, va_list vaList, std::string errorStr);
	};
}
