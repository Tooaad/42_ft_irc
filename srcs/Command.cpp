/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:23:15 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/20 18:19:19 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"
#include "../includes/Pass.hpp"

IRC::Command::Command()
{
}

IRC::Command::Command(std::string str)
{
    // Command* t = new IRC::Pass();
    cmd_map["/PASS"] = new IRC::Pass();
    // cmd_map["/NICK"] = new IRC::Nick();
    // cmd_map["/USER"] = new IRC::User();
    // cmd_map.insert(std::make_pair("/PASS", new IRC::Pass()));

    
    this->command = str.substr(0, str.find(" "));
    this->args = str.substr(str.find(" "), str.size());
}

IRC::Command::~Command()
{
}

// IRC::Command::Command(const IRC::Command& other)
// {
// }

void IRC::Command::detectCommand(void) const
{


}
