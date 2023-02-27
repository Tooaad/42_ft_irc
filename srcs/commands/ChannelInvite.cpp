/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelInvite.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:20:01 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/27 12:23:02 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/ChannelInvite.hpp"


IRC::ChannelInvite::ChannelInvite() {}
IRC::ChannelInvite::~ChannelInvite() {}

void	IRC::ChannelInvite::exec(IRC::Server* server, IRC::User& user)
{
	(void) server;
	(void) user;
}
