/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Username.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:54:33 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/28 15:03:05 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Username.hpp"


IRC::Username::Username() {}
IRC::Username::~Username() {}

void	IRC::Username::exec(IRC::Server* server, IRC::User& user)
{
	if (server->getPassword().size() > 0 && user.getPassword() != server->getPassword())
		return ;
	std::vector<std::string> argSplit = splitString(this->args, " ", 3);
	if (argSplit.size() < 4)
		return setError(ERR_NEEDMOREPARAMS, *server, user, 1, this->command.c_str());
	for (std::vector<IRC::User>::iterator it = server->getUsers().begin(); it != server->getUsers().end(); it++)
	{	
		if ((argSplit.at(0)).compare(it.base()->getUser()) == 0)
			return setError(ERR_ALREADYREGISTRED, *server, user, 0);
	}

	user.setUser(argSplit.at(0));
	// user.setHostname(argSplit.at(1));
	user.setServername(argSplit.at(2));
	if (argSplit.at(3).at(0) == ':')
	{
		argSplit.at(3).erase(0, 1);
		user.setRealname(argSplit.at(3));
		return ;
	}
	user.setRealname(splitString(argSplit.at(3), " ", 1)[0]);
}
