/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:46:20 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/07 16:14:55 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Quit.hpp"


IRC::Quit::Quit() {}
IRC::Quit::~Quit() {}

void	IRC::Quit::exec(IRC::Server* server, IRC::User& user)
{
	std::string message;
	
	if (args.size() > 0)
		message = "Quit: " + args;
	else
		message = "Quit: " + user.getNick();
		
	server->closeClient(user.getSocket(), message);
}
