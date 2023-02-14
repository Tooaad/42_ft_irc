/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:05:45 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/14 17:14:40 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Pong.hpp"


IRC::Pong::Pong() {}
IRC::Pong::~Pong() {}

void IRC::Pong::exec(IRC::Server* server, IRC::User& user)
{
	std::string recepStr = splitString(this->args, " ")[0];

	std::vector<IRC::User>::iterator receptor = findUser(server->getUsers(), recepStr);
	if (receptor == server->getUsers().end())
		return ;
	
	receptor->sendMessage("PING");

	// user.setTimeout() = time(0);
	(void)server;
	(void)user;
	
	// if (user.getTimeout() > server->getTimeout())
	//     // exit timeout
	//     return ;
}
