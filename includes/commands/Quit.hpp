/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:46:08 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/01 11:50:22 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"
#include <sstream>

namespace IRC
{
	class Command;

	class Quit : public Command
	{
		private:
			std::vector<Channel> channelsArray;

		public:
			Quit();
			virtual ~Quit();

			void exec(Server* server, User& user);

		private:
			void	parseArgs(Server* server);
			void	printNames(std::vector<Channel>::iterator itBegin, std::vector<Channel>::iterator itEnd);
	};
}
