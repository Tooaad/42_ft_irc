/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:05:45 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/06 18:21:57 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Pong.hpp"

IRC::Pong::Pong() {}
IRC::Pong::~Pong() {}

void IRC::Pong::exec(IRC::Server* server, IRC::User& user)
{
    // if (user.getTimeout() > server->getTimeout())
    //     // exit timeout
    //     return ;
    (void)server;
    (void)user;
}
