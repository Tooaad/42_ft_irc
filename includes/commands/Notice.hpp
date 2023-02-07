/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:12:55 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/07 10:51:58 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"

namespace IRC
{
	class Server;
	class Command;

	class Notice : public Command
	{
		public:
			Notice();
			virtual ~Notice();

			void	exec(IRC::Server* server, IRC::User& user);
	};
}
