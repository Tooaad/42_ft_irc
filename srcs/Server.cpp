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


IRC::Server::Server()
{
}

IRC::Server::Server(std::string pwd)
{
	this->pwd = pwd;
}

IRC::Server::~Server()
{
}

void IRC::Server::connectNetwork(std::string *args)
{
	(void)args;
}

int IRC::Server::createNetwork(std::string *args)
{
	(void)args;
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

	EV_SET(change_event, sSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);

	if (kevent(kq, change_event, 1, NULL, 0, NULL) == -1)
	{
		perror("kevent");
		return -1;
	}

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
				clientDisconnected(event_fd);

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
	client.clientSetup();

	EV_SET(this->change_event, client.getSocket(), EVFILT_READ, EV_ADD, 0, 0, NULL);
	if (kevent(this->kq, this->change_event, 1, NULL, 0, NULL) < 0)
	{
		perror("kevent error");
		return -1;
	}

	this->users.push_back(IRC::User(client.getSocket()));
	return 0;
}

void IRC::Server::clientDisconnected(int event_fd)
{
	std::cout << "Client has disconnected" << std::endl;
	close(event_fd);
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

	std::string message(buf);
	message = trim_endl(message); // TODO: leaks?

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
	IRC::User user = findUser(this->getUsers(), event_fd);
	if (!user.isAuthenticated())
		registration(user, message);

	if (!user.isAuthenticated())
		return -1;
	
	
	/*
	// Todo: Comprobar si ocurre alguna vez para borrar sino
	if (bytesRec == 0)
	{
		std::cout << "Client disconnected " << std::endl;
		return -1;
	}
	*/

	std::cout << "Msg from " << event_fd << ": " << std::string(buf, 0, bytesRec) << std::endl;

	for (size_t i = 0; i < users.size(); i++)
		send(users[i].getSocket(), buf, bytesRec + 1, 0);
	return 0;
}

void IRC::Server::registration(IRC::User user, std::string message) {
	if (this->pwd.size() > 0)
	{
		// Command cmd(message)
		std::string tmpPwd = parsePwd(message, "PASS ");
		if (tmpPwd.compare("") != 0)
		{
			user.setPassword(tmpPwd);

			std::cout << "Server Pass: '" << this->pwd << "'" << std::endl;
			std::cout << "User Pass: '" << user.getPassword() << "'" << std::endl;

			if (this->pwd.size() > 0 && user.getPassword().compare(this->pwd) != 0)
			{
				std::string error_msg = "<client> :Password incorrect\n";
				send(user.getSocket(), error_msg.c_str(), error_msg.size(), 0);
				clientDisconnected(user.getSocket());
			}
		}
	}
	
	// if (user.getPassword().size() > 0 || this->pwd.size() == 0)
	// {
		user.setUser("TEST");
		user.setNick("TEST");
		std::cout << "user" << std::endl;

		user.changeAuthenticated(); 				// true 
		std::cout << "authenticated" << std::endl;
	// }

	// if (user.getPassword().size() > 0 && user.getNick().size() > 0 && user.getUser().size() > 0 && !user.isAuthenticated())
	// {
	// }	

	if (user.isAuthenticated() == false)
	{
		std::string error_msg = "Not authenticated! Provide PASS, NICK and USER\n";
		send(user.getSocket(), error_msg.c_str(), error_msg.size(), 0);
	}
}

int IRC::Server::getSocket(void) const
{
	return this->sSocket;
}

int IRC::Server::getKq(void)
{
	return this->kq;
}

struct kevent *IRC::Server::getEvent(void)
{
	return &this->event[0];
}

struct kevent *IRC::Server::getChangeEvent(void)
{
	return &this->change_event[0];
}

std::vector<IRC::User> IRC::Server::getUsers(void)
{
	return this->users;
}

std::string IRC::parsePwd(std::string buf, std::string command) {
	if (buf.substr(0, 5) == command)
		return buf.substr(5, buf.size() - 1);
	return "";
}
