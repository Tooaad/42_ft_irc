/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:14:35 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/20 18:12:20 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>


namespace IRC
{
	class Command
	{
		enum Err {HAZLO, KEPA};
		
		private:
			static std::map<std::string, Command*> cmd_map;

		public:

			Command();
			Command(std::string str);
			Command(const Command& other);
			Command operator=(const Command& other);
			~Command();

			void detectCommand(void) const;
			virtual void exec(void) const;

		protected:

			std::string		command;
			int				id;
			std::string		args;
			int				argc;
			
			std::string		res;
			std::string		error;
			int				errn;
			
	};
}

