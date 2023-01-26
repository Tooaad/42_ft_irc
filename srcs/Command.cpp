/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:23:15 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/26 20:29:59 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"
#include "../includes/commands/Pass.hpp"
#include "../includes/commands/Nick.hpp"
#include "../includes/commands/Username.hpp"
#include "../includes/commands/ChannelJoin.hpp"
#include "../includes/commands/ChannelPart.hpp"

IRC::Command::Command()
{
}

// TODO: Quitar el / inicial en los comandos antes de guardar y tambien para comprobar
std::map<std::string, IRC::Command*> IRC::Command::cmd_map;
IRC::Command::Command(std::string str)
{
	cmd_map["/PASS"] = new IRC::Pass();
	cmd_map["/NICK"] = new IRC::Nick();
	cmd_map["/USER"] = new IRC::Username();
	cmd_map["/JOIN"] = new IRC::ChannelJoin();
	cmd_map["/PART"] = new IRC::ChannelPart();

	std::vector<std::string> argsArray = splitString(str, " ", 1);
	this->command = argsArray.at(0);
	std::transform(this->command.begin(), this->command.end(), this->command.begin(), ::toupper);   // transform command type to upper anyways

	if (argsArray.size() > 1)
		this->args = argsArray.at(1);

	std::cout << "------- Command parsing -------" << std::endl;
	std::cout << " Command: '" << command << "'" << std::endl;
	std::cout << " Args:    '" << args << "'" << std::endl;
	std::cout << "-------------------------------" << std::endl;
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
	this->replyNo = other.replyNo;
	this->replyMsg = other.replyMsg;
	this->errorNo = other.errorNo;
	this->errorMsg = other.errorMsg;
	
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
	t->answer(user);
}

void IRC::Command::exec(IRC::Server* server, IRC::User& user)
{
	std::cout << "GUAU" <<  std::endl;
	(void)server;
	(void)user;
}

void IRC::Command::answer(IRC::User& user)
{
	replyMsg = replyMsg + "\n";
	errorMsg = errorMsg + "\n";
	
	if (this->errorNo != 0)
		send(user.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
	else if (this-> replyNo != 0)
		send(user.getSocket(), replyMsg.c_str(), replyMsg.size(), 0);
	
}

void IRC::Command::setReply(ReplyNos replyNo, int n, ...)
{
	va_list vaList;
	va_start(vaList, n);

	this->replyNo = replyNo;
	
	switch (replyNo)
	{
		case TEST:
			this->replyMsg += expandMessage(n, vaList, "% :Bad Channel Mask");
			break;
		default:
			break;
	}
	
	va_end(vaList);
}

void IRC::Command::setError(ErrorNos errorNo, int n, ...)
{
	va_list vaList;
	va_start(vaList, n);

	this->errorNo = errorNo;
	
	switch (errorNo)
	{
		case ERR_BADCHANMASK:
			this->errorMsg = expandMessage(n, vaList, "% :Bad Channel Mask");
			break;
		case ERR_NOTREGISTERED:
			this->errorMsg = expandMessage(n, vaList, ":You have not registered");
			break;
		case ERR_NEEDMOREPARAMS:
			this->errorMsg = expandMessage(n, vaList, "% :Not enough parameters");
			break;
		case ERR_INVITEONLYCHAN:
			this->errorMsg = expandMessage(n, vaList, "% :Cannot join channel (+i)");
			break;
		case ERR_BADCHANNELKEY:
			this->errorMsg = expandMessage(n, vaList, "% :Cannot join channel (+k)");
			break;
		case ERR_NOSUCHCHANNEL:
			this->errorMsg = expandMessage(n, vaList, "% :No such channel");
			break;
		case ERR_NOTONCHANNEL:
			this->errorMsg = expandMessage(n, vaList, "% :You're not on that channel");
			break;
		case ERR_NONICKNAMEGIVEN:
			this->errorMsg = expandMessage(n, vaList, " :No nickname given");
			break;
		case ERR_ERRONEUSNICKNAME:
			this->errorMsg = expandMessage(n, vaList, "% :Erroneus nickname");
			break;
		case ERR_NICKNAMEINUSE:
			this->errorMsg = expandMessage(n, vaList, "% :Nickname is already in use");
			break;
		default:
			break;
	}
	
	va_end(vaList);
}

std::string IRC::Command::expandMessage(int argCount, va_list vaList, std::string errorStr)
{
	size_t startPos;
	std::string vaValue;
	
	while ((startPos = errorStr.find('%')) != std::string::npos)
	{
		if (argCount > 0)
			vaValue = va_arg(vaList, char *);
		else
			vaValue = "";
		
		errorStr.replace(startPos, 1, vaValue);
		argCount--;
	}

	return errorStr;
}
