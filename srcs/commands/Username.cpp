/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cUsername.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:54:33 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/24 14:12:18 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Username.hpp"

IRC::Username::Username()
{
}

IRC::Username::~Username()
{
}

void IRC::Username::exec(IRC::Server* server, IRC::User& user)
{
	std::vector<std::string> argSplit = split_string(this->args);
	for (std::vector<IRC::User>::iterator it = server->getUsers().begin(); it != server->getUsers().end(); it++)
	{	
		if ((argSplit.at(0)).compare(it.base()->getUser()) == 0)
		{
			// chose other username error
			return ;
		}	
	}
	user.setUser(argSplit.at(0));
	// argSplit.at(1); hostname
	// argSplit.at(2); servername

	if (argSplit.at(3).at(0) == ':')
	{
		for (std::vector<IRC::User>::iterator it = argsSplit.begin()+3 ; it != argsSplit.end(); it++)		
			user.setRealname(user.getRealname + it.base()->getRealname());
	}
		
	(void) server;
	(void) user;
}
