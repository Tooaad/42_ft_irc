/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:46:08 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/07 12:01:23 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"


namespace IRC
{
	class Command;

	class Quit : public Command
	{
		public:
			Quit();
			virtual ~Quit();

			void	exec(Server* server, User& user);
	};
}
