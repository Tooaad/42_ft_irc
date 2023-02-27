/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:02 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/27 18:01:34 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/event.h> // kqueue
#include <vector>
#include "User.hpp"
#include "Command.hpp"
#include "utils.hpp"
#include "Channel.hpp"


#define PING_TIMEOUT 100
#define REG_TIMEOUT 30
#define KQUEUE_TIMEOUT 3


namespace IRC
{
	class User;
	class Channel;
	
	class Server
	{
		private:
			std::string						ip;
			int								sSocket;
			int								kq;
			std::string 					password;
			struct kevent					changeEvent[4];		// TODO: hay que ampliar? vector
			struct kevent					event[4];			// TODO: hay que ampliar? vector
			std::vector<User>				users;
			std::vector<std::string>		commands;
			std::vector<Channel>			channels;
			std::string						hostname;

		public:
			Server();
			Server(std::string password);
			Server(const Server &other);
			~Server();
			Server &operator=(const Server &other);

			/* -- Getters -- */
			std::string						getIp(void) const;
			int								getSocket(void) const;
			int								getKq(void) const;
			std::string						getPassword(void) const;
			struct kevent					*getChangeEvent(void);
			struct kevent					*getEvent(void);
			std::vector<User>&				getUsers(void);
			std::vector<Channel>&			getChannels(void);
			std::string						getHostname(void) const;
			std::vector<Channel>::iterator	findChannel(std::string name);

			/* -- Modifiers -- */
			void							setHostname(std::string hostname);
			void							addChannel(Channel& channel);
			void							removeChannel(Channel channel);
			void							updateUserInChannels(IRC::User user);

			/* -- Member functions -- */
			void							connectNetwork(std::string *args);
			int								createNetwork(std::string *args);
			int								loop(void);
			void							closeClient(User& user, std::string message);
			void							terminateServer(void);
			void							catchPing(void);
			
		private:
			/* -- Member functions -- */
			void							removeUser(User& user);
			int								saveIp(void);
			int								clientConnected(void);
			void							clientDisconnected(int eventFd);
			int								receiveMessage(int eventFd);
			void							registration(User& user, std::string password);
			int								throwError(std::string message);
			std::vector<IRC::User>			getReferencedUsers(User user);
			// void serverClose(void);
	};
}
