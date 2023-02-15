/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:05:45 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/14 17:31:07 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Ping.hpp"


IRC::Ping::Ping() {}
IRC::Ping::~Ping() {}

void	IRC::Ping::exec(IRC::Server* server, IRC::User& user)
{
	if (args.size() > 0)
	{
		args = ":" + server->getIp() +  " PONG " + this->args;
		user.sendMessage(args);
	}
}
