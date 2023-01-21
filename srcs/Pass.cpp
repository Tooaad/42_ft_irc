/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:15:21 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/21 01:25:11 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Pass.hpp"

IRC::Pass::Pass()
{
}

IRC::Pass::~Pass()
{
}

void IRC::Pass::exec()
{
	this->res = args.substr(0, args.find(" "));
	// if (res.compare("") == 0)
		// std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
	
	
	// std::string tmpPwd = parsePwd(message, "PASS ");
	// 	if (tmpPwd.compare("") != 0)
	// 	{
	// 		user.setPassword(tmpPwd);

	// 		std::cout << "Server Pass: '" << this->pwd << "'" << std::endl;
	// 		std::cout << "User Pass: '" << user.getPassword() << "'" << std::endl;

	// 		if (this->pwd.size() > 0 && user.getPassword().compare(this->pwd) != 0)
	// 		{
	// 			std::string error_msg = "<client> :Password incorrect\n";
	// 			send(user.getSocket(), error_msg.c_str(), error_msg.size(), 0);
	// 			clientDisconnected(user.getSocket());
	// 		}
	// 	}	
}
// args = user.pass
// 