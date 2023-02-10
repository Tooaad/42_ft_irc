/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:36:07 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/10 18:49:54 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"


IRC::Server::Server() {}

IRC::Server::Server(std::string password)
{
	this->timeout = 10;
	this->password = password;
}

IRC::Server::Server(const IRC::Server &other) { *this = other; }

IRC::Server::~Server()
{
	std::cout << ">> Server destructor" << std::endl;
	/*
		TODO:
		- Cerrar todas las conexiones de clentes.
		- Liberar todo.
	*/

	for (size_t i = 0; i < getUsers().size(); i++)
		this->users.erase(this->users.begin());
	
	if (close(getSocket()) == -1)
		throwError("Server close error");
}

IRC::Server &IRC::Server::operator=(const IRC::Server &other)
{
	if (this != &other)
	{
		this->ip = other.ip;
		this->sSocket = other.sSocket;
		this->kq = other.kq;
		this->password = other.password;
		this->timeout = other.timeout;
		this->users = other.users;
		this->commands = other.commands;
		this->channels = other.channels;
	}

	return *this;
}

/* -- Getters -- */
std::string								IRC::Server::getIp(void) const { return this->ip; }
int										IRC::Server::getSocket(void) const { return this->sSocket; }
int										IRC::Server::getKq(void) const { return this->kq; }
std::string								IRC::Server::getPassword(void) const { return this->password; }
struct kevent*							IRC::Server::getChangeEvent(void) { return &this->changeEvent[0]; }
struct kevent*							IRC::Server::getEvent(void) { return &this->event[0]; }
time_t									IRC::Server::getTimeout(void) const { return this->timeout; }
std::vector<IRC::User*>					IRC::Server::getUsers(void) { return this->users; }
std::vector<IRC::Channel*>				IRC::Server::getChannels(void) { return this->channels; }

std::vector<IRC::Channel*>::iterator		IRC::Server::getChannelIt(std::string name)
{
	std::vector<IRC::Channel*>::iterator it = this->channels.begin();
	
	for (; it != this->channels.end(); it++)
	{
		if ((*it)->getName().compare(name) == 0)
			return it;
	}
	return it;
}

/* -- Modifiers -- */
void	IRC::Server::addChannel(IRC::Channel* channel)
{
	this->channels.push_back(channel);
}

void	IRC::Server::removeChannel(IRC::Channel* channel)
{
	std::vector<IRC::Channel*>::iterator found = findChannel(this->channels, channel->getName());
	if (found != this->channels.end())
		this->channels.erase(found);
}

/* -- Member functions -- */
void IRC::Server::connectNetwork(std::string *args)
{
	(void)args;
}

int IRC::Server::createNetwork(std::string *args)
{
	if ((this->sSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return throwError("Error opening socket");

	// Bind the Socket to any free IP / Port
	sockaddr_in hint;
	hint.sin_family = AF_INET; // IPv4 type
	// hint.sin_addr.s_addr = INADDR_ANY;
	hint.sin_port = htons(atoi(args[0].c_str())); // Little Endian (for bigger numbers) | Host To Network Short
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
	int yes = 1;
	
	if (setsockopt(this->sSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		return throwError("Error could not reuse address");

	if (bind(this->sSocket, (struct sockaddr *)&hint, sizeof(hint)) < 0)
		return throwError("Error binding socket");

	if (fcntl(this->sSocket, F_SETFL, O_NONBLOCK) < 0)
		return throwError("Error making server socket non blocking");

	listen(this->sSocket, SOMAXCONN);

	this->kq = kqueue();

	EV_SET(this->changeEvent, this->sSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);

	if (kevent(this->kq, this->changeEvent, 1, NULL, 0, NULL) == -1)
		return throwError("kevent 1");

	if (saveIp() == -1)
		return -1;
	std::cout << "--- IP: " << this->ip << " ---" << std::endl;

	return 0;
}

int IRC::Server::loop(void)
{
	int	newEvents;

	// Server loop
	catchSignal();
	while (!socketKiller)
	{
		if ((newEvents = kevent(getKq(), NULL, 0, getEvent(), 1, NULL)) == -1)
			if (!socketKiller)
				return throwError("kevent 2");

		// kqueue events loop
		for (int i = 0; i < newEvents; i++)
		{
			int eventFd = getEvent()[i].ident;

			// Client disconnected
			if (getEvent()[i].flags & EV_EOF)
				clientDisconnected(eventFd);

			// New client connected
			else if (eventFd == getSocket())
				clientConnected();

			// New message from client
			else if (getEvent()[i].filter & EVFILT_READ)
				receiveMessage(eventFd);
		}
	}
	return 0;
}

void	IRC::Server::closeClient(IRC::User* user, std::string message)
{
	// TODO: Tener en cuenta tambien referencias de MP

	std::vector<IRC::User*> referencedUsers = getReferencedUsers(user);

	for (std::vector<IRC::User*>::iterator it = referencedUsers.begin(); it != referencedUsers.end(); it++)
		(*it)->sendMessage(":" + user->getNick() + " QUIT :" + message + "\n");

	// TODO now: ??
	if (close(user->getSocket()) == -1)
		throwError("Client close error");
	else
		std::cout << user->getSocket() << " closed" << std::endl;

	removeUser(user);
}

/* -- Private Member functions */
void	IRC::Server::removeUser(IRC::User* user)
{
	
	std::vector<IRC::User*>::iterator found = std::find(this->users.begin(), this->users.end(), user);

	if (found == this->users.end())
		return ;
		
	for (size_t i = 0; i < this->channels.size(); i++)
	{
		// TODO now: refactor (user pointer)
		// this->channels[i].removeModerator(*found);
		// this->channels[i].removeOperator(*found);
		// this->channels[i].removeUser(*this, *found);
	}
	
	// TODO now: ??
	/*
	for (std::vector<IRC::Channel>::iterator channelIt = found->getJoinedChannels().begin(); channelIt != found->getJoinedChannels().end(); channelIt++)
	{
		channelIt->removeModerator(*found);
		channelIt->removeOperator(*found);
		channelIt->removeUser(*this, *found);
	}*/
	
	this->users.erase(found);
}

int		IRC::Server::saveIp(void)
{
	char				host[256];
	struct hostent*		hostEntry;

	if (gethostname(host, sizeof(host)) == -1)
		return throwError("Error getting ip: gethostname");
	
	hostEntry = gethostbyname(host);
	if (!hostEntry)
		this->ip = "127.0.0.1";
	else
		this->ip = inet_ntoa(*((struct in_addr*) hostEntry->h_addr_list[0]));
	
	return 0;
}

int		IRC::Server::clientConnected(void)
{
	IRC::Client client(this->sSocket);
	client.setup();

	EV_SET(this->changeEvent, client.getSocket(), EVFILT_READ, EV_ADD, 0, 0, NULL);
	if (kevent(this->kq, this->changeEvent, 1, NULL, 0, NULL) < 0)
		return throwError("kevent 3");

	IRC::User* user = new IRC::User(client.getSocket());
	this->users.push_back(user);
	return 0;
}

void	IRC::Server::clientDisconnected(int eventFd)
{
	std::vector<IRC::User*>::iterator userIt = findUser(this->users, eventFd);
	if (userIt == this->users.end())
		return ;

	closeClient(*userIt, "Quit: Connection closed");
}

int		IRC::Server::receiveMessage(int eventFd)
{
	char buf[4096];
	int bytesRec;

	memset(buf, 0, 4096);
	if (fcntl(eventFd, F_SETFL, O_NONBLOCK) < 0)
		return throwError("Error making client socket non blocking");

	if ((bytesRec = recv(eventFd, buf, 4096, 0)) == -1)
	{
		std::cout << "Error in recv(). Quitting" << std::endl;
		return -1;
	}

	std::vector<IRC::User*>::iterator found = findUser(this->users, eventFd);
	if (found == this->users.end()) // TODO: que hacer si no encontramos usuario
		return -1;

	IRC::User* user = *found; // TODO: .base()

	std::string message(buf);

	
	// std::cout << "*** Buffer prev: '" << user.getBuffer() << "'" << std::endl;
	// std::cout << "*** New buffer: '" << message << "'" << std::endl;
	message.erase(remove(message.begin(), message.end(), '\r'), message.end());
	// std::cout << "*** New buffer replaced: '" << message << "'" << std::endl;
	user->appendBuffer(message);
	std::cout << "Command: '" << user->getBuffer() << "'" << std::endl;


	std::vector<std::string> messageSplit = splitString(user->getBuffer(), "\n");
	if (messageSplit.size() == 0)
		return 0;

	user->clearBuffer();
	
	if (messageSplit[messageSplit.size() - 1].size() == 0)
		messageSplit.erase(messageSplit.end() - 1);
	else
	{
		user->appendBuffer(messageSplit[messageSplit.size() - 1]);
		messageSplit.erase(messageSplit.end() - 1);
	}

	for (std::vector<std::string>::iterator it = messageSplit.begin(); it != messageSplit.end(); it++)
	{
		//std::cout << "*** Split: '" << *it << "'" << std::endl;
		if (!user->isAuthenticated())
			registration(user, *it);
		else
		{
			// Detect commands once registered
			IRC::Command cmd(*it);
			cmd.detectCommand(this, user);
		}

		printUsers(this->users);
		printChannels(channels);
		std::cout << std::endl << "*** *** *** *** *** *** *** *** *** *** ***" << std::endl << std::endl;
	}
	
	messageSplit.clear();

	/* 
	// Todo: Comprobar si ocurre alguna vez para borrar sino
	if (bytesRec == 0)
	{
		std::cout << "Client disconnected " << std::endl;
		return -1;
	}
	*/
	// std::cout << "Msg from " << eventFd << ": " << std::string(buf, 0, bytesRec) << std::endl;

	/*
	for (size_t i = 0; i < users.size(); i++)
		send(users[i].getSocket(), buf, bytesRec + 1, 0);
	*/

	return 0;
}

void	IRC::Server::registration(IRC::User* user, std::string message)
{
	IRC::Command cmd(message);
	cmd.detectCommand(this, user);

	if (user->getPassword().size() > 0 && user->getNick().size() > 0 && user->getUser().size() > 0 && !user->isAuthenticated())
	{
		user->changeAuthenticated(); 				// true
		std::string errorMsg = "You have been authenticated!\n";
		user->sendMessage(errorMsg);
	}

	// if (user.isAuthenticated() == false)
	// {
	// 	std::string errorMsg = "Not authenticated! Provide PASS, NICK and USER\n";
	// 	user.sendMessage(errorMsg);
	// }
}

int		IRC::Server::throwError(std::string message)
{
	perror(message.c_str());
	return -1;
}

// TODO: refactor with pointers
std::vector<IRC::User*>	IRC::Server::getReferencedUsers(IRC::User* user)
{
	std::vector<IRC::User*> referencedUsers;

	for (std::vector<IRC::User*>::iterator itUser = this->users.begin(); itUser != this->users.end(); itUser++)
	{
		if (*itUser == user)
			continue ;

		std::vector<IRC::Channel*> joinedChannels = user->getJoinedChannels();
		for (std::vector<IRC::Channel*>::iterator itChannel = joinedChannels.begin(); itChannel != joinedChannels.end(); itChannel++)
		{
			if ((*itUser)->isInChannel(*itChannel))
			{
				referencedUsers.push_back(*itUser);
				break ;
			}
			/*
				TODO: Usuarios referenciados por MP tambien hay que tener en cuenta
			*/
		}
	}

	return referencedUsers;
}
