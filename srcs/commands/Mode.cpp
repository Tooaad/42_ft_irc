/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:01:18 by gpernas-          #+#    #+#             */
/*   Updated: 2023/02/07 11:50:31 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Mode.hpp"

IRC::Mode::Mode() {}
IRC::Mode::~Mode() {}

// TODO: Proteger todas las llamadas a findUser
void IRC::Mode::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, *server, user, 0);

	if (this->args.size() == 0)
		setError(ERR_NEEDMOREPARAMS, *server, user, 1, command.c_str());

	if (this->args.at(0) == '#' || this->args.at(0) == '&')
	{
		// NeedMoreParams
		// ChannelModeIs
		// ChaNoPrivsNeeded
		// NoTonChannel
		// RPL_BANLIST
		// RPL_ENDOFBANLIST
		// Unknownmode
		// NoSuchChannel
		
		std::vector<std::string> argSplit = splitString(this->args, " ");
		std::vector<IRC::Channel>::iterator receptor = server->getChannelIt(argSplit[0]);
		if (receptor.base() == NULL)
			return setError(ERR_NOSUCHCHANNEL, *server, user, 1, argSplit[0].c_str());
		
		if (!user.isInChannel(*receptor))
			return setError(ERR_NOTONCHANNEL, *server, user, 1, argSplit[1].c_str()); //revisar

		if(!receptor->isOperator(user))
			return setError(ERR_CHANOPRIVSNEEDED, *server, user, 1, argSplit[1].c_str());

		if (argSplit.size() > 1)
		{
			for (size_t i = 1; i < argSplit[1].size(); i++)
			{
				if (argSplit[1].at(i) == 'o')
				{
					if (argSplit.size() < 2)
						return setError(ERR_NEEDMOREPARAMS, *server, user, 1, command.c_str());
					if (argSplit[1].at(0) == '+')
						receptor->addOperator(*findUser(server->getUsers(), argSplit[2])); // gestionar 2o arg 
					else if (argSplit[1].at(0) == '-')
						receptor->removeOperator(*findUser(server->getUsers(), argSplit[2])); // gestionar 2o arg 
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
				else if (argSplit[1].at(i) == 'n')	// NO FUNCIONA??
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
			// else if (argSplit[1].at(i) == 'b')
				}
				else if (argSplit[1].at(i) == 'v')
				{
					if (argSplit.size() < 2)
						return setError(ERR_NEEDMOREPARAMS, *server, user, 1, command.c_str());
					if (argSplit[1].at(0) == '+')
						receptor->addModerator(*findUser(server->getUsers(), argSplit[2])); // gestionar 2o arg 
					else if (argSplit[1].at(0) == '-')
						receptor->removeModerator(*findUser(server->getUsers(), argSplit[2])); // gestionar 2o arg 
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
			setReply(RPL_CHANNELMODEIS, *server, user, 7,
						receptor->isSecret()? "+s ":"",
						receptor->isInviteOnly()? "+i ":"",
						receptor->isFreeTopic()? "+t ":"",
						receptor->isPublicMsg()? "+n ":"",
						receptor->isModerated()? "+m ":"",
						receptor->hasMax()? printChannelMax(*receptor).c_str():"",
						receptor->hasPassword()? printPassword(*receptor).c_str():"");
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

std::string IRC::Mode::printChannelMax(IRC::Channel recept)
{
	std::string str("+l ");
	std::stringstream ss;
	ss << recept.getMaxUsers();
	str += ss.str();
	// str += ", ";
	return str;
}

std::string IRC::Mode::printPassword(IRC::Channel recept)
{
	std::string str("+k ");
	str += recept.getPassword();
	// str += ", ";
	return str;
}
