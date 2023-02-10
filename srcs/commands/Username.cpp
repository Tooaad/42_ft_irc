/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Username.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:54:33 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/10 17:09:09 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Username.hpp"


IRC::Username::Username() {}
IRC::Username::~Username() {}

void	IRC::Username::exec(Server* server, User* user)
{
	if (server->getPassword().size() > 0 && user->getPassword() != server->getPassword())
		return ;
	std::vector<std::string> argSplit = splitString(this->args, " ", 3);
	if (argSplit.size() < 4)
		return setError(ERR_NEEDMOREPARAMS, server, user, 1, this->command.c_str());
		
	std::vector<IRC::User*> users = server->getUsers();
	for (std::vector<IRC::User*>::iterator it = users.begin(); it != users.end(); it++)
	{	
		if ((argSplit.at(0)).compare((*it)->getUser()) == 0)
			return setError(ERR_ALREADYREGISTRED, server, user, 0);
	}
	user->setUser(argSplit.at(0));
	user->setHostname(argSplit.at(1));
	user->setServername(argSplit.at(2));
	if (argSplit.at(3).at(0) == ':')
		argSplit.at(3).erase(0, 1);
	user->setRealname(argSplit.at(3));
}
