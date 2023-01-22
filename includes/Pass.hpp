/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:20:40 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/22 16:13:54 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"

namespace IRC 
{
	class Server;
	class Command;
	class Pass : public Command
	{
		public:
			Pass();
			Pass(Pass const& other);
			virtual ~Pass();

			void exec(IRC::Server* server, IRC::User user);
	};
}

