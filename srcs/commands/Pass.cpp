/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:15:21 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/07 16:14:55 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Pass.hpp"


IRC::Pass::Pass() {}
IRC::Pass::~Pass() {}

// Block message if password is not provide
void IRC::Pass::exec(IRC::Server* server, IRC::User& user)
{
	if (this->args.size() < 1)
	{
		setError(ERR_NEEDMOREPARAMS, *server, user, 1, this->command.c_str());
		return ;
	}
	if (user.isAuthenticated())
	{
		setError(ERR_ALREADYREGISTRED, *server, user, 0);
		return ;
	}
	user.setPassword(args.substr(0, args.find(" ")));
	if (server->getPassword().size() > 0 && user.getPassword().compare(server->getPassword()) != 0)
	{
		std::string error_msg = "<client> :Password incorrect\n";
		send(user.getSocket(), error_msg.c_str(), error_msg.size(), 0);
		server->closeClient(user.getSocket(), "Quit: Password incorrect");
	}
}
