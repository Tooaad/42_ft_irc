/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 02:21:33 by gpernas-          #+#    #+#             */
/*   Updated: 2023/03/01 12:03:05 by karisti-         ###   ########.fr       */
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
		return setReply(ERR_NONICKNAMEGIVEN, *server, user, 0);
		
	std::transform(this->args.begin(), this->args.end(), this->args.begin(), ::tolower);   // transform command type to lower anyways
	
	for (size_t i = 0; i != this->args.size(); i++)
		if (!std::isprint(this->args.at(i)) || this->args.at(i) == '#')
			return setReply(ERR_ERRONEUSNICKNAME, *server, user, 1, this->args.c_str());
			
	if (findUser(server->getUsers(), this->args) != server->getUsers().end())
		return setReply(ERR_NICKNAMEINUSE, *server, user, 1, this->args.c_str());

	user.setNick(splitString(this->args, " ").at(0));
	server->updateUserInChannels(user);
}
