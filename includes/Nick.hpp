/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 02:14:55 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/24 02:15:28 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"

namespace IRC 
{
	class Server;
	class Command;
	class Nick : public Command
	{
		public:
			Nick();
			Nick(Nick const& other);
			virtual ~Nick();

			void exec(IRC::Server* server, IRC::User& user);
	};
}

