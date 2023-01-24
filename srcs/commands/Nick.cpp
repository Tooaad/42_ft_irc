/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 02:21:33 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/24 13:01:40 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Nick.hpp"

IRC::Nick::Nick()
{
}

IRC::Nick::~Nick()
{
}

void IRC::Nick::exec(IRC::Server* server, IRC::User& user)
{	
	/*
	if (user.getPassword().size() > 0 || server->getPWD().size() == 0)
		// error no password provide
		return ;
	*/
	for (std::vector<IRC::User>::iterator it = server->getUsers().begin(); it != server->getUsers().end(); it++)
	{	
		if (this->args.compare(it.base()->getNick()) == 0)
		{
			// chose other nick error
			return ;
		}	
	}
	user.setNick(args); //parsear args con substr
}
