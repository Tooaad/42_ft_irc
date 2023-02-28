/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Username.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:54:33 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/28 14:44:41 by karisti-         ###   ########.fr       */
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
		return setReply(ERR_NEEDMOREPARAMS, *server, user, 1, this->command.c_str());
	for (std::vector<IRC::User>::iterator it = server->getUsers().begin(); it != server->getUsers().end(); it++)
	{	
		if ((argSplit.at(0)).compare(it.base()->getUser()) == 0)
			return setReply(ERR_ALREADYREGISTRED, *server, user, 0);
	}
	user.setUser(argSplit.at(0));
	// user.setHostname(argSplit.at(1)); TODO: esto?
	user.setServername(argSplit.at(2));
	if (argSplit.at(3).at(0) == ':')
		argSplit.at(3).erase(0, 1);
	user.setRealname(argSplit.at(3));
}
