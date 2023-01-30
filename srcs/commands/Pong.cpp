/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:05:45 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/30 11:01:58 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Pong.hpp"

IRC::Pong::Pong()
{
}

IRC::Pong::~Pong()
{
}

void IRC::Pong::exec(IRC::Server* server, IRC::User& user)
{
    // if (user.getTimeout() > server->getTimeout())
    //     // exit timeout
    //     return ;
        (void)server;
    (void)user;
}