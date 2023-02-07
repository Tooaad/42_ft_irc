/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   this->cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:43:29 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/19 12:22:31 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"


IRC::Server::Server() {}
IRC::Server::Server(const IRC::Server &other) { *this = other; }
IRC::Server::~Server() {}

IRC::Server::Server(std::string password)
{
	this->timeout = 10;
	this->password = password;
}

IRC::Server &IRC::Server::operator=(const IRC::Server &other)
{
	if (this != &other)
	{
		sSocket = other.sSocket;
		kq = other.kq;
		password = other.password;
		timeout = other.timeout;
		users = other.users;
		commands = other.commands;
		channels = other.channels;
		ip = other.ip;
	}
	return *this;
}



void IRC::Server::connectNetwork(std::string *args)
{
	(void)args;
}

int IRC::Server::createNetwork(std::string *args)
{
	if ((this->sSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Error opening socket");
		return -1;
	}

	// Bind the Socket to any free IP / Port
	sockaddr_in hint;
	hint.sin_family = AF_INET; // IPv4 type
	// hint.sin_addr.s_addr = INADDR_ANY;
	hint.sin_port = htons(atoi(args[0].c_str())); // Little Endian (for bigger numbers) | Host To Network Short
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

	if (bind(sSocket, (struct sockaddr *)&hint, sizeof(hint)) < 0)
	{
		perror("Error binding socket");
		return -1;
	}

	if (fcntl(sSocket, F_SETFL, O_NONBLOCK) < 0)
	{
		perror("Error making server socket non blocking");
		return -1;
	}

	listen(sSocket, SOMAXCONN);

	kq = kqueue();

	EV_SET(changeEvent, sSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);

	if (kevent(kq, changeEvent, 1, NULL, 0, NULL) == -1)
	{
		perror("kevent");
		return -1;
	}

	if (this->saveIp() == -1)
		return -1;
	std::cout << "--- IP: " << this->ip << " ---" << std::endl;

	return 0;
}

int IRC::Server::loop(void)
{
	int new_events;

	// Server loop
	while (true)
	{
		if ((new_events = kevent(this->getKq(), NULL, 0, this->getEvent(), 1, NULL)) == -1)
		{
			perror("kevent");
			return -1;
		}

		// kqueue events loop
		for (int i = 0; i < new_events; i++)
		{
			int event_fd = this->getEvent()[i].ident;

			// Client disconnected
			if (this->getEvent()[i].flags & EV_EOF)
				clientDisconnected(event_fd, "Quit: Connection closed");

			// New client connected
			else if (event_fd == this->getSocket())
				clientConnected();

			// New message from client
			else if (this->getEvent()[i].filter & EVFILT_READ)
				receiveMessage(event_fd);
		}
	}
	return 0;
}

int IRC::Server::clientConnected(void)
{
	IRC::Client client(this->sSocket);
	client.setup();

	EV_SET(this->changeEvent, client.getSocket(), EVFILT_READ, EV_ADD, 0, 0, NULL);
	if (kevent(this->kq, this->changeEvent, 1, NULL, 0, NULL) < 0)
	{
		perror("kevent error");
		return -1;
	}

	this->users.push_back(IRC::User(client.getSocket()));
	return 0;
}

void IRC::Server::closeConnection(int event_fd, std::string message)
{
	this->clientDisconnected(event_fd, message);
}

void IRC::Server::clientDisconnected(int event_fd, std::string message)
{
	std::vector<IRC::User>::iterator found = std::find(users.begin(), users.end(), User(event_fd));
	if (found != users.end())
	{
		std::cout << message << std::endl;
		users.erase(found);
	}

	close(event_fd); // TODO: ver errores o si es bloqueante
}

int IRC::Server::receiveMessage(int event_fd)
{
	char buf[4096];
	int bytesRec;

	memset(buf, 0, 4096);
	if (fcntl(event_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		perror("Error making client socket non blocking");
		return -1;
	}

	if ((bytesRec = recv(event_fd, buf, 4096, 0)) == -1)
	{
		std::cout << "Error in recv(). Quitting" << std::endl;
		return -1;
	}

	std::vector<IRC::User>::iterator found = std::find(users.begin(), users.end(), User(event_fd));
	if (found == users.end()) // TODO: que hacer si no encontramos usuario
		return -1;

	IRC::User& user = *found.base();

	std::string message(buf);

	
	// std::cout << "*** Buffer prev: '" << user.getBuffer() << "'" << std::endl;
	// std::cout << "*** New buffer: '" << message << "'" << std::endl;
	message.erase(remove(message.begin(), message.end(), '\r'), message.end());
	// std::cout << "*** New buffer replaced: '" << message << "'" << std::endl;
	user.appendBuffer(message);
	std::cout << "Command: '" << user.getBuffer() << "'" << std::endl;


	std::vector<std::string> messageSplit = splitString(user.getBuffer(), "\n");
	if (messageSplit.size() == 0)
		return 0;

	user.clearBuffer();
	
	if (messageSplit[messageSplit.size() - 1].size() == 0)
		messageSplit.erase(messageSplit.end() - 1);
	else
	{
		user.appendBuffer(messageSplit[messageSplit.size() - 1]);
		messageSplit.erase(messageSplit.end() - 1);
	}

	user.setPassword("12"); // TODO: Remove
	for (std::vector<std::string>::iterator it = messageSplit.begin(); it != messageSplit.end(); it++)
	{
		//std::cout << "*** Split: '" << *it << "'" << std::endl;
		if (!user.isAuthenticated())
			registration(user, *it);
		else
		{
			// Detect commands once registered
			IRC::Command cmd(*it);
			cmd.detectCommand(this, user);
		}

		printUsers(users);
		printChannels(channels);
		std::cout << std::endl << "*** *** *** *** *** *** *** *** *** *** ***" << std::endl << std::endl;
	}
	
	messageSplit.clear();




/*
	pass 12
	nick karisti
	user\d

	pass 12
	nick karisti
	user karisti 0 * :Kepa
*/

	// message = trimEndl(message); // TODO: leaks?


	


	/* 
	// Todo: Comprobar si ocurre alguna vez para borrar sino
	if (bytesRec == 0)
	{
		std::cout << "Client disconnected " << std::endl;
		return -1;
	}
	*/
	// std::cout << "Msg from " << event_fd << ": " << std::string(buf, 0, bytesRec) << std::endl;

	/*
	for (size_t i = 0; i < users.size(); i++)
		send(users[i].getSocket(), buf, bytesRec + 1, 0);
	*/

	return 0;
}

		/*
		CAP LS 302
		PASS
		NICK and USER
		Capability Negotiation
		SASL (if negotiated)
		CAP END

			Command: USER
			Parameters: <username> 0 * <realname>

			ERR_PASSWDMISMATCH (464) 
			"<client> :Password incorrect"
		*/
void IRC::Server::registration(IRC::User& user, std::string message) {
	
	IRC::Command cmd(message);
	cmd.detectCommand(this, user);

	if (user.getPassword().size() > 0 && user.getNick().size() > 0 && user.getUser().size() > 0 && !user.isAuthenticated())
	{
		user.changeAuthenticated(); 				// true
		std::string error_msg = "You have been authenticated!\n";
		send(user.getSocket(), error_msg.c_str(), error_msg.size(), 0);
	}

	// if (user.isAuthenticated() == false)
	// {
	// 	std::string error_msg = "Not authenticated! Provide PASS, NICK and USER\n";
	// 	send(user.getSocket(), error_msg.c_str(), error_msg.size(), 0);
	// }
}

int IRC::Server::getSocket(void) const
{
	return this->sSocket;
}

int IRC::Server::getKq(void) const
{
	return this->kq;
}

std::string IRC::Server::getPassword(void) const
{
	return this->password;
}

time_t IRC::Server::getTimeout(void) const
{
	return this->timeout;
}

struct kevent *IRC::Server::getEvent(void)
{
	return &this->event[0];
}

struct kevent *IRC::Server::getChangeEvent(void)
{
	return &this->changeEvent[0];
}

std::vector<IRC::User>& IRC::Server::getUsers(void)
{
	return this->users;
}

std::vector<IRC::Channel>& IRC::Server::getChannels(void)
{
	return this->channels;
}

std::vector<IRC::Channel>::iterator IRC::Server::getChannelIt(std::string name)
{
	std::vector<IRC::Channel>::iterator it = channels.begin();
	
	for (; it != channels.end(); it++)
	{
		if (it->getName().compare(name) == 0)
			return it;
	}
	
	return it;
}

void	IRC::Server::addChannel(IRC::Channel& channel)
{
	channels.push_back(channel);
}

void IRC::Server::removeChannel(IRC::Channel channel)
{
	std::vector<IRC::Channel>::iterator found = std::find(channels.begin(), channels.end(), channel);
	
	if (found != channels.end())
		channels.erase(found);
	
}

int IRC::Server::saveIp(void)
{
	char host[256];
	struct hostent *host_entry;

	if (gethostname(host, sizeof(host)) == -1)
	{
		perror("Error getting ip: gethostname");
		return -1;
	}
	host_entry = gethostbyname(host);
	if (!host_entry)
		this->ip = "127.0.0.1";
	else
		this->ip = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
	return 0;
}

std::string IRC::Server::getIp(void)
{
	return this->ip;
}
