/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:15:21 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/26 21:43:24 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Pass.hpp"

IRC::Pass::Pass()
{
}

IRC::Pass::~Pass()
{
}

// Block message if password is not provide

void IRC::Pass::exec(IRC::Server* server, IRC::User& user)
{
	if (this->args.size() < 1)
	{
		setError(ERR_NEEDMOREPARAMS, 1, this->command);
		return ;
	}
	if (user.isAuthenticated())
	{
		setError(ERR_ALREADYREGISTRED, 0);
		return ;
	}
	user.setPassword(args.substr(0, args.find(" ")));
	if (server->getPWD().size() > 0 && user.getPassword().compare(server->getPWD()) != 0)
	{
		std::string error_msg = "<client> :Password incorrect\n";
		send(user.getSocket(), error_msg.c_str(), error_msg.size(), 0);
		server->clientDisconnected(user.getSocket());
	}	
}
