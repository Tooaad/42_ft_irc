/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:20:40 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/24 13:01:06 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"

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

			void exec(IRC::Server* server, IRC::User& user);
	};
}
