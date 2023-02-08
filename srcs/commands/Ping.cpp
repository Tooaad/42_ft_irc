/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:05:45 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/08 11:31:32 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Ping.hpp"


IRC::Ping::Ping() {}
IRC::Ping::~Ping() {}

void	IRC::Ping::exec(IRC::Server* server, IRC::User& user)
{
	std::string recepStr = splitString(this->args, " ")[0];

	std::vector<IRC::User>::iterator receptor = findUser(server->getUsers(), recepStr);
	if (receptor == server->getUsers().end())
		return ;
	
	receptor->sendMessage("PING");

	// user.setTimeout() = time(0);
	(void)server;
	(void)user;
}
