/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:05:45 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/28 20:15:13 by gpernas-         ###   ########.fr       */
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
    if (user.getTimeout() > server->getTimeout())
        // exit timeout
        return ;
}