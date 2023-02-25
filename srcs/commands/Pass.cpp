/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:15:21 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/25 12:35:23 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Pass.hpp"


IRC::Pass::Pass() {}
IRC::Pass::~Pass() {}

void IRC::Pass::exec(IRC::Server* server, IRC::User& user)
{
	if (this->args.size() < 1)
		return setError(ERR_NEEDMOREPARAMS, *server, user, 1, this->command.c_str());
	if (user.isAuthenticated())
		return setError(ERR_ALREADYREGISTRED, *server, user, 0);
	user.setPassword(args.substr(0, args.find(" ")));
	
	if (server->getPassword().size() > 0 && user.getPassword().compare(server->getPassword()) != 0)
		setError(ERR_PASSWDMISMATCH, *server, user, 0);
}
