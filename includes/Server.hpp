/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:02 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/01 13:01:52 by karisti-         ###   ########.fr       */
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
#include <signal.h>
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
		int				sSocket;
		int				kq;
		std::string 	pwd;
		struct kevent	change_event[4]; // TODO: hay que ampliar? vector
		struct kevent	event[4];		   // TODO: hay que ampliar? vector
		time_t			timeout;
		std::vector<IRC::User>		users;
		std::vector<std::string>	commands;
		std::vector<IRC::Channel>	channels;
		std::string		ip;

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
		Server(std::string pwd);
		Server(const Server &other);
		Server &operator=(const Server &other);
		~Server();

		int createNetwork(std::string *args);
		void connectNetwork(std::string *args);
		int loop(void);
		int clientConnected(void);
		void clientDisconnected(int event_fd, std::string message);
		int receiveMessage(int event_fd);
		void registration(IRC::User& user, std::string PWD);
		// void serverClose(void);

		int getSocket(void) const;
		int getKq(void) const;
		std::string getPWD(void) const;
		struct kevent *getEvent(void);
		struct kevent *getChangeEvent(void);
		time_t getTimeout(void) const;
		std::vector<User>& getUsers(void);
		std::vector<Channel>& getChannels(void);
		std::vector<Channel>::iterator getChannelIt(std::string name);
		void addChannel(Channel& channel);
		void removeChannel(Channel channel);
		int saveIP(void);
		std::string getIP(void);
	};
	std::string parsePwd(std::string buf, std::string command);
	void	recSignals();
	void	handleSig(int sig);
}

extern bool terminate;
