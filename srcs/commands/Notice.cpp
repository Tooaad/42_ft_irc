/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:13:36 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/10 17:42:15 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Notice.hpp"


IRC::Notice::Notice() {}
IRC::Notice::~Notice() {}

void	IRC::Notice::exec(IRC::Server *server, IRC::User* user)
{
	if (!user->isAuthenticated())
		return ;
	
	if (this->args.size() == 0)
		return ;

	std::vector<std::string> argSplit = splitString(this->args, " ", 1);
	if (argSplit[1].size() == 0)
		return ;

	if (argSplit[0].at(0) == '#')
	{
		std::vector<IRC::Channel*>::iterator receptor = server->getChannelIt(argSplit[0]);
		if (receptor.base() == NULL)
			return ;
			
		if(!user->isInChannel(*receptor) || !(*receptor)->isPublicMsg() || ((*receptor)->isModerated() && !(*receptor)->isOperator(user) && !(*receptor)->isModerator(user)))
			return ;

		(*receptor)->sendMessageToUsers(":" + user->getNick() + " NOTICE " + argSplit[0] + " " + argSplit[1] + "\n");
	}
	else
	{
		std::vector<IRC::User*>::iterator receptor = findUser(server->getUsers(), argSplit[0]);
		if (receptor == server->getUsers().end())
			return ;
	
		argSplit[1] = ":" + user->getNick() + " NOTICE " + (*receptor)->getNick() + " " + argSplit[1] + "\n";
		(*receptor)->sendMessage(argSplit[1]);
	}
}
