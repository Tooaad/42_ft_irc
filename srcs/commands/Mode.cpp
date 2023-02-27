/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:01:18 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/27 18:00:55 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Mode.hpp"


IRC::Mode::Mode() {}
IRC::Mode::~Mode() {}

void	IRC::Mode::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, *server, user, 0);

	if (this->args.size() == 0)
		return setError(ERR_NEEDMOREPARAMS, *server, user, 1, command.c_str());

	if (this->args.at(0) == '#' || this->args.at(0) == '&')
	{	
		std::vector<std::string> argSplit = splitString(this->args, " ");
		std::vector<IRC::Channel>::iterator receptor = server->getChannelIt(argSplit[0]);
		if (receptor == server->getChannels().end())
			return setError(ERR_NOSUCHCHANNEL, *server, user, 1, argSplit[0].c_str());
		
		if (!user.isInChannel(*receptor))
			return setError(ERR_NOTONCHANNEL, *server, user, 1, argSplit[0].c_str());

		if(!receptor->isOperator(user))
			return setError(ERR_CHANOPRIVSNEEDED, *server, user, 1, argSplit[0].c_str());

		if (argSplit.size() > 1)
		{
			for (size_t i = 1; i < argSplit[1].size(); i++)
			{
				if (argSplit[1].at(i) == 'o')
				{
					if (argSplit.size() < 2)
						return setError(ERR_NEEDMOREPARAMS, *server, user, 1, command.c_str());
					if (argSplit[1].at(0) == '+')
					{
						std::vector<IRC::User>::iterator userIt = findUser(server->getUsers(), argSplit[2]);
						if (userIt != server->getUsers().end())
							receptor->addOperator(*userIt, server); // gestionar 2o arg
					}
					else if (argSplit[1].at(0) == '-')
					{
						std::vector<IRC::User>::iterator userIt = findUser(server->getUsers(), argSplit[2]);
						if (userIt != server->getUsers().end())
							receptor->removeOperator(*userIt, server); // gestionar 2o arg
					}
				}
				else if (argSplit[1].at(i) == 's')
				{
					if (argSplit[1].at(0) == '+' && !receptor->isSecret())
						receptor->changeSecrecy();
					else if (argSplit[1].at(0) == '-' && receptor->isSecret())
						receptor->changeSecrecy();
				}
				else if (argSplit[1].at(i) == 'i')
				{
					if (argSplit[1].at(0) == '+' && !receptor->isInviteOnly())
						receptor->changeInviteOnly();
					else if (argSplit[1].at(0) == '-' && receptor->isInviteOnly())
						receptor->changeInviteOnly();
				}
				else if (argSplit[1].at(i) == 't')
				{
					if (argSplit[1].at(0) == '+' && !receptor->isFreeTopic())
						receptor->changeFreeTopic();
					else if (argSplit[1].at(0) == '-' && receptor->isFreeTopic())
						receptor->changeFreeTopic();
				}
				else if (argSplit[1].at(i) == 'n')
				{
					if (argSplit[1].at(0) == '+' && !receptor->isPublicMsg())
						receptor->changePublicMsg();
					else if (argSplit[1].at(0) == '-' && receptor->isPublicMsg())
						receptor->changePublicMsg();
				}
				else if (argSplit[1].at(i) == 'm')
				{
					if (argSplit[1].at(0) == '+' && !receptor->isModerated())
						receptor->changeModerated();
					else if (argSplit[1].at(0) == '-' && receptor->isModerated())
						receptor->changeModerated();
				}
				else if (argSplit[1].at(i) == 'l')
				{
					if (argSplit.size() < 2)
						return setError(ERR_NEEDMOREPARAMS, *server, user, 1, command.c_str());
					if (argSplit[1].at(0) == '+')
						receptor->setMaxUsers(atoi(argSplit[2].c_str())); 
					else if (argSplit[1].at(0) == '-')
						receptor->setMaxUsers(0);
				}
				else if (argSplit[1].at(i) == 'v')
				{
					if (argSplit.size() < 2)
						return setError(ERR_NEEDMOREPARAMS, *server, user, 1, command.c_str());
					if (argSplit[1].at(0) == '+')
					{
						std::vector<IRC::User>::iterator userIt = findUser(server->getUsers(), argSplit[2]);
						if (userIt != server->getUsers().end())
							receptor->addModerator(*userIt, server); // gestionar 2o arg
					}
					else if (argSplit[1].at(0) == '-')
					{
						std::vector<IRC::User>::iterator userIt = findUser(server->getUsers(), argSplit[2]);
						if (userIt != server->getUsers().end())
							receptor->removeModerator(*userIt, server); // gestionar 2o arg
					}
				}
				else if (argSplit[1].at(i) == 'k')
				{
					if (argSplit.size() < 2)
						return setError(ERR_NEEDMOREPARAMS, *server, user, 1, command.c_str());
					if (argSplit[1].at(0) == '+')
						receptor->setPassword(argSplit[2]);		// gestionar 2o arg
					else if (argSplit[1].at(0) == '-')
						receptor->setPassword(argSplit[2]);
				}
				else
					return setError(ERR_UNKNOWNMODE, *server, user, 1, argSplit[i].c_str());
			}
		}
		else
		{
			std::string mode = "";
			receptor->isSecret()? mode += " +s,": "";
			receptor->isFreeTopic()? mode += " +t,": "";
			receptor->isPublicMsg()? mode += " +n,": "";
			receptor->isModerated()? mode += " +m,": "";
			receptor->isInviteOnly()? mode += " +i,": "";
			receptor->hasMax()? mode += printChannelMax(*receptor): "";
			receptor->hasPassword()? mode += printPassword(*receptor): "";
			if (mode.length() > 0)
			{
				mode.erase(0, 1);
				mode.erase(mode.length() - 1, 1);
			}
			setReply(RPL_CHANNELMODEIS, *server, user, 1, mode.c_str());
		}
	}
	else
	{
		std::vector<std::string> argSplit = splitString(this->args, " ", 1);
		// if (argSplit.size() < 2)
		// 	return setError(ERR_NEEDMOREPARAMS, *server, user, 1, this->command.c_str());
		std::vector<IRC::User>::iterator receptor = findUser(server->getUsers(), argSplit[0]);
		if (receptor == server->getUsers().end())
			return setError(ERR_NOSUCHNICK, *server, user, 1, argSplit[0].c_str());
			
		if (!(*receptor == user))
			return setError(ERR_USERSDONTMATCH, *server, user, 0);
	
		if (argSplit.size() > 1)
		{
			for (size_t i = 1 ; i < argSplit[1].size(); i++)
			{
				if (argSplit[1].at(i) == 'i')
				{
					if(argSplit[1].at(0) == '+' && !user.isInvisible())
						user.changeInvisibility();
					else if (argSplit[1].at(0) == '-' && user.isInvisible())
						user.changeInvisibility();
				}
				else if (argSplit[1].at(i) == 's')
				{
					if(argSplit[1].at(0) == '+' && !user.isSubscribed())
						user.changeSubscription();
					else if (argSplit[1].at(0) == '-' && user.isSubscribed())
						user.changeSubscription();
				}
				else if (argSplit[1].at(i) == 'o')
				{
					if(argSplit[1].at(0) == '+')
						return ;
					else if (argSplit[1].at(0) == '-')
						user.deOp();
				}
				else 
					return setError(ERR_UMODEUNKNOWNFLAG, *server, user, 0);
			}
		}
		else
			setReply(RPL_UMODEIS, *server, user, 3, user.isInvisible()? "+i":"", user.isSubscribed()? "+s":"", user.isOp()? "+o":"");
	}
}

std::string		IRC::Mode::printChannelMax(IRC::Channel recept)
{
	std::string str(" +l ");
	std::stringstream ss;
	ss << recept.getMaxUsers();
	str += ss.str();
	str += ",";
	return str;
}

std::string		IRC::Mode::printPassword(IRC::Channel recept)
{
	std::string str(" +k ");
	str += recept.getPassword();
	str += ",";
	return str;
}
