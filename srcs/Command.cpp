/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:23:15 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/24 13:07:37 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"
#include "../includes/commands/Pass.hpp"
#include "../includes/commands/Nick.hpp"
#include "../includes/commands/ChannelJoin.hpp"

IRC::Command::Command()
{
}

IRC::Command::Command(std::string str)
{
	cmd_map["/PASS "] = new IRC::Pass();
	cmd_map["/NICK "] = new IRC::Nick();
	// cmd_map["/USER"] = new IRC::User();
	cmd_map["/JOIN "] = new IRC::ChannelJoin();

	this->command = str.substr(0, str.find(" ") + 1);
	std::transform(this->command.begin(), this->command.end(), this->command.begin(), ::toupper);   // transform command type to upper anyways

// >>>PROTEGER<<<
	this->args = str.substr(str.find(" ") + 1, str.size());

	// std::cout << "'" << command << "'" << std::endl;
	// std::cout << args << std::endl;
}

IRC::Command::~Command()
{
}

IRC::Command::Command(const IRC::Command& other)
{
	*this = other;
}

IRC::Command& IRC::Command::operator=(const IRC::Command& other)
{
	this->command = other.command;
	this->args = other.args;
	return *this;
}

IRC::Command* IRC::Command::find(std::string key) const
{
	std::map<std::string, Command*>::const_iterator found = cmd_map.find(key);
	
	if (found != cmd_map.end())
		return found->second;
	
	return NULL;
}

void IRC::Command::detectCommand(IRC::Server* server, IRC::User& user)
{
// >>>>PROTEGER<<<<
	IRC::Command* t = find(this->command);
	
	if (!t)
		return ;
    
    // if (dynamic_cast <IRC::Pass *> (t))
    //     continue ;
    // else if (dynamic_cast <IRC::User *> (t) || dynamic_cast <IRC::Nick *> (t))
    //     condicion
    // else
    //     condicion autenticado


	*t = *this;
	
	// std::cout << typeid(t).name() <<  std::endl;
	// std::cout << t->args <<  std::endl;
	
	t->exec(server, user);
}

void IRC::Command::exec(IRC::Server* server, IRC::User& user)
{
	std::cout << "GUAU" <<  std::endl;
	(void)server;
	(void)user;
}
