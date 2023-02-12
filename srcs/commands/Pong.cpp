/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:05:45 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/12 20:39:23 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Pong.hpp"


IRC::Pong::Pong() {}
IRC::Pong::~Pong() {}

void IRC::Pong::exec(IRC::Server* server, IRC::User& user)
{
	(void) server;
	if (args.size() > 0)
	{
		args = "PONG " + this->args;
		user.sendMessage(args);
	}
		
	// if (user.getTimeout() > server->getTimeout())
	//     // exit timeout
	//     return ;
}
