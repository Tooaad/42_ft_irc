/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:15:21 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/25 13:53:29 by gpernas-         ###   ########.fr       */
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
	user.setPassword(args.substr(0, args.find(" ")));
	std::cout << "'" << args << "'" << std::endl;
	std::cout << "'" << server->getPWD() << "'" << std::endl;
	if (server->getPWD().size() > 0 && user.getPassword().compare(server->getPWD()) != 0)
	{
		std::string error_msg = "<client> :Password incorrect\n";
		send(user.getSocket(), error_msg.c_str(), error_msg.size(), 0);
		server->clientDisconnected(user.getSocket());
	}
	
	// if (res.compare("") == 0)
		// std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
	
}
