/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:23:15 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/22 19:03:00 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"
#include "../includes/Pass.hpp"

IRC::Command::Command()
{
}

IRC::Command::Command(std::string str)
{
    cmd_map["/PASS "] = new IRC::Pass();
    // cmd_map["/NICK"] = new IRC::Nick();
    // cmd_map["/USER"] = new IRC::User();

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
    return cmd_map.find(key)->second;
}

void IRC::Command::detectCommand(IRC::Server* server, IRC::User user)
{
// >>>>PROTEGER<<<<
    IRC::Command* t = find(this->command); 
    t->operator=(*this);
    
    // std::cout << typeid(t).name() <<  std::endl;
    // std::cout << t->args <<  std::endl;
    
    t->exec(server, user);
}

void IRC::Command::exec(IRC::Server* server, IRC::User user)
{
    std::cout << "GUAU" <<  std::endl;
    (void)server;
    (void)user;
}
