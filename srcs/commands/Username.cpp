/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Username.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:54:33 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/25 14:00:22 by gpernas-         ###   ########.fr       */
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
	if (server->getPWD().size() > 0 && user.getPassword() != server->getPWD())
		// error no password provide
		return ;	
	std::vector<std::string> argSplit = splitString(this->args, " ", 3);
	if (argSplit.size() < 4)
		// error need more params
	for (std::vector<IRC::User>::iterator it = server->getUsers().begin(); it != server->getUsers().end(); it++)
	{	
		if ((argSplit.at(0)).compare(it.base()->getUser()) == 0)
		{
			// error already registered
			return ;
		}	
	}
	user.setUser(argSplit.at(0));
	// argSplit.at(1); hostname
	// argSplit.at(2); servername
	if (argSplit.at(3).at(0) == ':')
		argSplit.erase(argSplit.begin());
	
	// Not setting realname
	user.setRealname(argSplit.at(3));

}
