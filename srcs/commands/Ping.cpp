/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:05:45 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/30 17:34:51 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Ping.hpp"

IRC::Ping::Ping()
{
}

IRC::Ping::~Ping()
{
}

void IRC::Ping::exec(IRC::Server* server, IRC::User& user)
{
    std::string recep_str = splitString(this->args, " ").at(0);
    User receptor = findUser(server->getUsers(), recep_str);
    send(receptor.getSocket(), "PING", 4, 0);
    
    // user.setTimeout() = time(0);
    (void)server;
    (void)user;
    
}