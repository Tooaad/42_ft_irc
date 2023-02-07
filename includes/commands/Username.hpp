/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Username.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:51:15 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/07 10:51:31 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"

namespace IRC
{
	class Server;
	class Command;

	class Username : public Command
	{
		public:
			Username();
			virtual ~Username();

			void	exec(IRC::Server* server, IRC::User& user);
	};
}
