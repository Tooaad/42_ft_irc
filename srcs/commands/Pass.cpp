/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:15:21 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/10 17:07:44 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Pass.hpp"


IRC::Pass::Pass() {}
IRC::Pass::~Pass() {}

// Block message if password is not provide
void IRC::Pass::exec(Server* server, User* user)
{
	if (this->args.size() < 1)
	{
		setError(ERR_NEEDMOREPARAMS, server, user, 1, this->command.c_str());
		return ;
	}
	if (user->isAuthenticated())
	{
		setError(ERR_ALREADYREGISTRED, server, user, 0);
		return ;
	}
	user->setPassword(args.substr(0, args.find(" ")));
	if (server->getPassword().size() > 0 && user->getPassword().compare(server->getPassword()) != 0)
	{
		std::string error_msg = "<client> :Password incorrect\n";
		user->sendMessage(error_msg);
		server->closeClient(user, "Quit: Password incorrect");
	}
}
