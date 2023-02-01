/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:12:55 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/01 16:13:13 by gpernas-         ###   ########.fr       */
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

			void exec(IRC::Server* server, IRC::User& user);

	};
}
