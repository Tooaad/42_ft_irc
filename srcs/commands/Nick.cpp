/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 02:21:33 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/13 11:09:59 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Nick.hpp"


IRC::Nick::Nick() {}
IRC::Nick::~Nick() {}

void	IRC::Nick::exec(IRC::Server* server, IRC::User& user)
{	

	if (server->getPassword().size() > 0 && user.getPassword() != server->getPassword())
		return ;			
	if (this->args.size() < 1)
		{
			setError(ERR_NONICKNAMEGIVEN, *server, user, 0);
			return ;
		}
	std::transform(this->args.begin(), this->args.end(), this->args.begin(), ::tolower);   // transform command type to lower anyways
	for (size_t i = 0; i != this->args.size(); i++)
		if (!std::isprint(this->args.at(i)) || this->args.at(i) == '#')
			{
				setError(ERR_ERRONEUSNICKNAME, *server, user, 1, this->args.c_str());
				return ; 
			}	
	for (std::vector<IRC::User>::iterator it = server->getUsers().begin(); it != server->getUsers().end(); it++)
	{	
		if (this->args.compare(it.base()->getNick()) == 0)
		{
				setError(ERR_NICKNAMEINUSE, *server, user, 1, this->args.c_str());
				return ; 
		}
	}
	user.setNick(splitString(this->args, " ").at(0));
}
