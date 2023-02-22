/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:14:35 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/22 15:49:35 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <algorithm>
#include <typeinfo>
#include <map>
#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"


namespace IRC
{
	class Server;
	class User;
	class Channel;
	
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
				ERR_TOOMANYCHANNELS=405,
				ERR_USERSDONTMATCH=502,
				ERR_UMODEUNKNOWNFLAG=501,
				ERR_CHANOPRIVSNEEDED=482,
				ERR_UNKNOWNMODE=472
				// ERR_BANNEDFROMCHAN
			};

			enum ReplyNos {
				/*
				RPL_WELCOME=001,
				RPL_YOURHOST=002,
				RPL_CREATED=003,
				RPL_MYINFO=004,
				RPL_ISUPPORT=005,
				*/
				RPL_NAMREPLY=353,
				RPL_ENDOFNAMES=366,
				RPL_AWAY=301,
				RPL_NOTOPIC=331,
				RPL_TOPIC=332,
				RPL_UMODEIS=221,
				RPL_LISTSTART=321,
				RPL_LIST=322,
				RPL_LISTEND=323,
				RPL_CHANNELMODEIS=324
			};
	
		protected:
			std::string		command;
			std::string		args;
			std::string		replyMsg;
			std::string		errorMsg;
			int				replyNo;
			int				errorNo;
			// int			id;
			// int			argc;
		
		private:
			static			std::map<std::string, Command*> cmd_map;

		public:
			Command();
			Command(std::string str);
			Command(const Command& other);
			virtual ~Command();
			Command& operator=(const Command& other);

			/* -- Setters -- */
			void			setReply(ReplyNos replyNo, Server server, User user, int n, ...);
			void			setError(ErrorNos errorNo, Server server, User user, int n, ...);
			void			setActionInReply(Server server, User user, Channel channel, std::string action);
			
			/* -- Member functions -- */
			void			detectCommand(Server* server, User& user);
		
		private:
			/* -- Member functions -- */
			Command*		find(std::string key) const;
			virtual void	exec(Server* server, User& user);
			void			answer(User& user);
			std::string		expandMessage(int argCount, va_list vaList, std::string errorStr) const;
	};
}
