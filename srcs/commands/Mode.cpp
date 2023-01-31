/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:01:18 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/31 19:08:58 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/Mode.hpp"

IRC::Mode::Mode()
{
}

IRC::Mode::~Mode()
{
}

void IRC::Mode::exec(IRC::Server* server, IRC::User& user)
{
	if (!user.isAuthenticated())
		return setError(ERR_NOTREGISTERED, 0);

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
			return setError(ERR_NOSUCHCHANNEL, 1, argSplit[0].c_str());

		if (!user.isInChannel(*receptor))
			return setError(ERR_NOTONCHANNEL, 1, argSplit[1].c_str()); //revisar

		if(!receptor->isOperator(user))
			return setError(ERR_CHANOPRIVSNEEDED, 1, argSplit[1].c_str()); //revisar

		for (size_t i = 1; i < argSplit[1].size(); i++)
		{
			if (argSplit[1].at(i) == 'o')
			{
				if (argSplit[1].at(0) == '+')
					receptor->addOperator(findUser(server->getUsers(), argSplit[2])); // gestionar 2o arg 
				else if (argSplit[1].at(0) == '-')
					receptor->removeOperator(findUser(server->getUsers(), argSplit[2])); // gestionar 2o arg 
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
				if (argSplit[1].at(0) == '+')
					receptor->setMaxUsers(atoi(argSplit[2].c_str())); 
				else if (argSplit[1].at(0) == '-')
					receptor->setMaxUsers(0);

			// else if (argSplit[1].at(i) == 'b')
			}
			else if (argSplit[1].at(i) == 'v')
			{
				if (argSplit[1].at(0) == '+')
					receptor->addModerator(findUser(server->getUsers(), argSplit[2])); // gestionar 2o arg 
				else if (argSplit[1].at(0) == '-')
					receptor->removeModerator(findUser(server->getUsers(), argSplit[2])); // gestionar 2o arg 
			}
			else if (argSplit[1].at(i) == 'k')
			{
				if (argSplit[1].at(0) == '+')
					receptor->setPassword(argSplit[2]);		// gestionar 2o arg
				else if (argSplit[1].at(0) == '-')
					receptor->setPassword(argSplit[2]);
			}
			else
				return setError(ERR_UMODEUNKWOWNFLAG, 0); // ERR_UMODEUNKWOWN
		}
		
	}
	else
	{
		std::vector<std::string> argSplit = splitString(this->args, " ", 1);
		if (argSplit.size() != 2)
			return setError(ERR_NEEDMOREPARAMS, 1, this->command.c_str());
		
		IRC::User receptor = findUser(server->getUsers(), argSplit[0]);	
		if (receptor == NULL)
			return setError(ERR_NOSUCHNICK, 1, argSplit[0].c_str());
	
		if (!(receptor == user))
			return setError(ERR_USERSDONTMATCH, 0);
	
		if (argSplit[1].size() > 1)
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
					return setError(ERR_UMODEUNKWOWNFLAG, 0);
			}
		}
		setReply(RPL_UMODEIS, 6, "i: ", user.isInvisible(), "s: ", user.isSubscribed(), "o: ", user.isOp());
	}
}


// mode user +is 