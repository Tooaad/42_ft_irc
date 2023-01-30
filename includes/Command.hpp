/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:14:35 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/30 18:32:43 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <algorithm>
#include <typeinfo>
#include <map>
#include "Server.hpp"
#include "User.hpp"

/*

RPL_TOPIC
*/

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
				ERR_NICKNAMEINUSE=433,
				ERR_ALREADYREGISTRED=462,
				ERR_NORECIPTIENT=411,
				ERR_CANNOTSENDTOCHAN=404,
				ERR_WILDTOPLEVEL=414,
				ERR_NOSUCHNICK=401,
				ERR_NOTEXTTOSEND=412,
				ERR_NOTOPLEVEL=413,
				ERR_TOOMANYTARGETS=407,
				ERR_NOORIGIN=409,
				ERR_NOSUCHSERVER=402,
				ERR_CHANNELISFULL=471,
				ERR_TOOMANYCHANNELS=405
				// ERR_BANNEDFROMCHAN
			};

			enum ReplyNos {
				RPL_NAMREPLY=353,
				RPL_ENDOFNAMES=366,
				RPL_AWAY=301, 
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
