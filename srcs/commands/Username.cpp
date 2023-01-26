/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Username.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:54:33 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/26 21:23:17 by gpernas-         ###   ########.fr       */
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
		return ;	
	std::vector<std::string> argSplit = splitString(this->args, " ", 3);
	if (argSplit.size() < 4)
		{
			setError(ERR_NEEDMOREPARAMS, 1, this->command);
			return ;
		}
	for (std::vector<IRC::User>::iterator it = server->getUsers().begin(); it != server->getUsers().end(); it++)
	{	
		if ((argSplit.at(0)).compare(it.base()->getUser()) == 0)
		{
			setError(ERR_ALREADYREGISTRED, 0);
			return ;
		}
	}
	user.setUser(argSplit.at(0));
	user.setHostname(argSplit.at(1)); 
	user.setServername(argSplit.at(2)); 
	if (argSplit.at(3).at(0) == ':')
		argSplit.at(3).erase(0, 1);
	user.setRealname(argSplit.at(3));

}
