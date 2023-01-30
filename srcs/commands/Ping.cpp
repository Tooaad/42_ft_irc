/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:05:45 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/30 11:01:36 by gpernas-         ###   ########.fr       */
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
    // send(user.getSocket(). "PING", 4, 0);
    // user.setTimeout() = time(0);
    (void)server;
    (void)user;
    
}