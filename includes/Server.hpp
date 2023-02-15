/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:02 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/15 11:23:28 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>	   // fcntl
#include <sys/event.h> // kqueue
#include <vector>
#include "User.hpp"
#include "Client.hpp"
#include "Command.hpp"
#include "utils.hpp"
#include "Channel.hpp"


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
			time_t							timeout;
			std::vector<User>				users;
			std::vector<std::string>		commands;
			std::vector<Channel>			channels;
			

			// //			◦ If host, port_network and password_network aren’t given, you must create a new IRC network
			// //			◦ host is the hostname on which IRC must connect to join a already existing network
			// 			std::string		hostname;
			// //			◦ port_network is the server port on which IRC must connect on host
			// 			int				port_network;
			// //			◦ password_network is the password needed to connect on host
			// 			std::string		pw_network;
			// //			◦ port is the port number on which your server will accept incoming connections.
			// 			int				port;
			// //			◦ password is the password needed by any IRC client who wants to connect to your server.
			// 			std::string		password;

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
			time_t							getTimeout(void) const;
			std::vector<User>&				getUsers(void);
			std::vector<Channel>&			getChannels(void);
			std::vector<Channel>::iterator	getChannelIt(std::string name);

			/* -- Modifiers -- */
			void							addChannel(Channel& channel);
			void							removeChannel(Channel channel);
			void							updateUserInChannels(std::string prevNick, IRC::User user);

			/* -- Member functions -- */
			void							connectNetwork(std::string *args);
			int								createNetwork(std::string *args);
			int								loop(void);
			void							closeClient(User& user, std::string message);
			void							terminateServer(void);
			void							catchPing(int eventFd);
			
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
