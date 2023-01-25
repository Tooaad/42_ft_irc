/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 02:21:33 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/25 13:49:25 by gpernas-         ###   ########.fr       */
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

	if (server->getPWD().size() > 0 && user.getPassword() != server->getPWD())
		// error no password provide
		return ;			
	if (this->args.size() < 0)
		// error no nickname given
		return ;
	for (size_t i = 0; i != this->args.size(); i++)
		if (!std::isprint(this->args.at(i)))
			// error char no printable
			return ;
	for (std::vector<IRC::User>::iterator it = server->getUsers().begin(); it != server->getUsers().end(); it++)
	{	
		if (this->args.compare(it.base()->getNick()) == 0)
		{
			// error nickname in use
			return ;
		}	
	}
	user.setNick(splitString(this->args, " ").at(0));
}
