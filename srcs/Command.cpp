/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:23:15 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/10 16:50:06 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"
#include "../includes/commands/Pass.hpp"
#include "../includes/commands/Nick.hpp"
#include "../includes/commands/Username.hpp"
#include "../includes/commands/Privmsg.hpp"
#include "../includes/commands/Notice.hpp"
#include "../includes/commands/Mode.hpp"
#include "../includes/commands/Quit.hpp"
#include "../includes/commands/ChannelJoin.hpp"
#include "../includes/commands/ChannelPart.hpp"
#include "../includes/commands/ChannelTopic.hpp"
#include "../includes/commands/ChannelNames.hpp"
#include "../includes/commands/ChannelList.hpp"


IRC::Command::Command()
{
	this->replyMsg = "";
	this->errorMsg = "";
	this->replyNo = 0;
	this->errorNo = 0;
}

std::map<std::string, IRC::Command*> IRC::Command::cmd_map;
IRC::Command::Command(std::string str)
{
	this->replyMsg = "";
	this->errorMsg = "";
	this->replyNo = 0;
	this->errorNo = 0;
	
	if (cmd_map.empty())
	{
		this->cmd_map["PASS"] = new IRC::Pass();
		this->cmd_map["NICK"] = new IRC::Nick();
		this->cmd_map["USER"] = new IRC::Username();
		this->cmd_map["PRIVMSG"] = new IRC::PrivMsg();
		this->cmd_map["NOTICE"] = new IRC::Notice();
		this->cmd_map["MODE"] = new IRC::Mode();
		this->cmd_map["JOIN"] = new IRC::ChannelJoin();
		this->cmd_map["PART"] = new IRC::ChannelPart();
		this->cmd_map["TOPIC"] = new IRC::ChannelTopic();
		this->cmd_map["NAMES"] = new IRC::ChannelNames();
		this->cmd_map["LIST"] = new IRC::ChannelList();
		this->cmd_map["QUIT"] = new IRC::Quit();
	}

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

IRC::Command::Command(const IRC::Command& other) { *this = other; }
IRC::Command::~Command() {}

IRC::Command& IRC::Command::operator=(const IRC::Command& other)
{
	this->command = other.command;
	this->args = other.args;
	this->replyMsg = other.replyMsg;
	this->errorMsg = other.errorMsg;
	this->replyNo = other.replyNo;
	this->errorNo = other.errorNo;
	
	return *this;
}

/* -- Setters -- */
void		IRC::Command::setReply(ReplyNos replyNo, IRC::Server* server, IRC::User* user, int n, ...)
{
	std::stringstream ss;

	va_list vaList;
	va_start(vaList, n);

	this->replyNo = replyNo;
	
	if (!this->replyMsg.empty())
		this->replyMsg += "\n";

	ss << replyNo;
	std::string replyNoStr = ss.str();
	// :127.0.0.1 353 karisti = #jeje :@karisti
	this->replyMsg += ":" + server->getIp() + " " + replyNoStr + " " + user->getNick() + " ";
	
	switch (replyNo)
	{
		case RPL_NAMREPLY:
			this->replyMsg += expandMessage(n, vaList, "= % :%");
			break;
		case RPL_ENDOFNAMES:
			this->replyMsg += expandMessage(n, vaList, "% :End of /NAMES list");
			break;
		case RPL_AWAY:
			this->replyMsg += expandMessage(n, vaList, "% :%<AWAY MSG>");
			break;
		case RPL_NOTOPIC:
			this->replyMsg += expandMessage(n, vaList, "% :No topic is set");
			break;
		case RPL_TOPIC:
			this->replyMsg += expandMessage(n, vaList, "% :%");
			break;
		case RPL_UMODEIS:
			this->replyMsg += expandMessage(n, vaList, "% % %");
			break;
		case RPL_LISTSTART:
			this->replyMsg += expandMessage(n, vaList, "Channel :Users  Name");
			break;
		case RPL_LIST:
			this->replyMsg += expandMessage(n, vaList, "% % :%");
			break;
		case RPL_LISTEND:
			this->replyMsg += expandMessage(n, vaList, ":End of /LIST");
			break;
		case RPL_CHANNELMODEIS:
			this->replyMsg += expandMessage(n, vaList, "% % % % % % %");
			break;
		default:
			break;
	}
	
	va_end(vaList);
}

void		IRC::Command::setError(ErrorNos errorNo, IRC::Server* server, IRC::User* user, int n, ...)
{
	std::stringstream ss;
	
	va_list vaList;
	va_start(vaList, n);

	this->errorNo = errorNo;

	ss << errorNo;
	std::string errorNoStr = ss.str();
	// :127.0.0.1 353 karisti = #jeje :@karisti
	this->errorMsg = ":" + server->getIp() + " " + errorNoStr + " " + user->getNick() + " ";
	
	switch (errorNo)
	{
		case ERR_BADCHANMASK:
			this->errorMsg += expandMessage(n, vaList, "% :Bad Channel Mask");
			break;
		case ERR_NOTREGISTERED:
			this->errorMsg += expandMessage(n, vaList, ":You have not registered");
			break;
		case ERR_NEEDMOREPARAMS:
			this->errorMsg += expandMessage(n, vaList, "% :Not enough parameters");
			break;
		case ERR_INVITEONLYCHAN:
			this->errorMsg += expandMessage(n, vaList, "% :Cannot join channel (+i)");
			break;
		case ERR_BADCHANNELKEY:
			this->errorMsg += expandMessage(n, vaList, "% :Cannot join channel (+k)");
			break;
		case ERR_NOSUCHCHANNEL:
			this->errorMsg += expandMessage(n, vaList, "% :No such channel");
			break;
		case ERR_NOTONCHANNEL:
			this->errorMsg += expandMessage(n, vaList, "% :You're not on that channel");
			break;
		case ERR_NONICKNAMEGIVEN:
			this->errorMsg += expandMessage(n, vaList, " :No nickname given");
			break;
		case ERR_ERRONEUSNICKNAME:
			this->errorMsg += expandMessage(n, vaList, "% :Erroneus nickname");
			break;
		case ERR_NICKNAMEINUSE:
			this->errorMsg += expandMessage(n, vaList, "% :Nickname is already in use");
			break;
		case ERR_ALREADYREGISTRED:
			this->errorMsg += expandMessage(n, vaList, " :You may not reregister");
			break;
		case ERR_NORECIPTIENT:
			this->errorMsg += expandMessage(n, vaList, " :No recipient given %");;
			break;
		case ERR_CANNOTSENDTOCHAN:
			this->errorMsg += expandMessage(n, vaList, "% :Cannot send to channel");
			break;
		case ERR_WILDTOPLEVEL:
			this->errorMsg += expandMessage(n, vaList, "% :Wildcard in toplevel");
			break;
		case ERR_NOSUCHNICK:
			this->errorMsg += expandMessage(n, vaList, "% :No such nick/channel");
			break;
		case ERR_NOTEXTTOSEND:
			this->errorMsg += expandMessage(n, vaList, " :No text to send");
			break;
		case ERR_NOTOPLEVEL:
			this->errorMsg += expandMessage(n, vaList, "% :No toplevel domain specified");
			break;
		case ERR_TOOMANYTARGETS:
			this->errorMsg += expandMessage(n, vaList, "% :Duplicate recipients. No message");
			break;
		case ERR_NOORIGIN:
			this->errorMsg += expandMessage(n, vaList, " :No origin specified");
			break;
		case ERR_NOSUCHSERVER:
			this->errorMsg += expandMessage(n, vaList, "% :No such server");
			break;
		case ERR_USERSDONTMATCH:
			this->errorMsg += expandMessage(n, vaList, " :Cant change mode for other users");
			break;
		case ERR_UMODEUNKNOWNFLAG:
			this->errorMsg += expandMessage(n, vaList, " :Unknown MODE flag");
			break;
		case ERR_UNKNOWNMODE:
			this->errorMsg += expandMessage(n, vaList, "% :is unknown mode char to me");
			break;
		case ERR_CHANOPRIVSNEEDED:
			this->errorMsg += expandMessage(n, vaList, "% :You're not channel operator");
			break;
		default:
			break;
	}
	
	va_end(vaList);
}

/* -- Member functions -- */
void		IRC::Command::detectCommand(IRC::Server* server, IRC::User* user)
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

/* -- Private member functions */
IRC::Command*	IRC::Command::find(std::string key) const
{
	std::map<std::string, Command*>::const_iterator found = this->cmd_map.find(key);
	
	if (found != this->cmd_map.end())
		return found->second;
	
	return NULL;
}

void			IRC::Command::exec(IRC::Server* server, IRC::User* user)
{
	std::cout << "GUAU" <<  std::endl;
	(void)server;
	(void)user;
}

void			IRC::Command::answer(IRC::User* user)
{
	this->replyMsg = this->replyMsg + "\n";
	this->errorMsg = this->errorMsg + "\n";
	
	if (this->errorNo != 0)
		user->sendMessage(errorMsg);
	else if (this->replyNo != 0)
		user->sendMessage(replyMsg);
}

std::string		IRC::Command::expandMessage(int argCount, va_list vaList, std::string errorStr) const
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
