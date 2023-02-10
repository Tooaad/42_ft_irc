/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Username.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:51:15 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/10 16:34:49 by karisti-         ###   ########.fr       */
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

			void	exec(Server* server, User* user);
	};
}
