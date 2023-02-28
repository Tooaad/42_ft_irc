/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelNames.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:10:06 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/28 12:15:59 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Command.hpp"


namespace IRC
{
	class ChannelNames : public Command
	{
		public:
			ChannelNames();
			virtual ~ChannelNames();

			void	exec(Server* server, User& user);

		private:
			void	printNames(Server server, User user, std::vector<Channel>::iterator itBegin, std::vector<Channel>::iterator itEnd);
	};
}
