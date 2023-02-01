/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:05:45 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/01 16:44:46 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Ping.hpp"

IRC::Ping::Ping()
{
}

IRC::Ping::~Ping()
{
}

void IRC::Ping::exec(IRC::Server* server, IRC::User& user)
{
	std::string recepStr = splitString(this->args, " ")[0];
	
	send(user.getSocket(), "PONG", 4, 0);
	
	// user.setTimeout() = time(0);
	(void)server;
	(void)user;
	
}
