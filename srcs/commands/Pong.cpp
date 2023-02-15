/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:05:45 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/15 12:38:36 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Pong.hpp"


IRC::Pong::Pong() {}
IRC::Pong::~Pong() {}

void IRC::Pong::exec(IRC::Server* server, IRC::User& user)
{
	if (args.size() < 1)
		return setError(ERR_NEEDMOREPARAMS, *server, user, 0);
	
	if (user.isPinged() == false)
		return ;

	if (args.compare(user.getPingKey()) == 0)
	{
		user.setTimeout(time(NULL));
		user.changeRequest(false);
	}
	else
		server->closeClient(user, "INCORRECT PING");
}
