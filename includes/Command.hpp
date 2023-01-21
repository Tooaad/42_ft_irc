/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:14:35 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/20 21:24:47 by gpernas-         ###   ########.fr       */
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
		
		public:
			static std::map<std::string, Command*> cmd_map;

		public:

			Command();
			Command(std::string str);
			Command(const Command& other);
			Command operator=(const Command& other);
			virtual ~Command();

			Command* find(std::string key) const;
			void detectCommand(void);
			virtual void exec(void) = 0;


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

