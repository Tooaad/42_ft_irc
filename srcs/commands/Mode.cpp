/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:01:18 by gpernas-          #+#    #+#             */
/*   Updated: 2023/01/31 13:39:11 by gpernas-         ###   ########.fr       */
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

	std::vector<std::string> argSplit = splitString(this->args, " ");
	if (this->args.at(0) == '#')
	{
		// NeedMoreParams
		// ChannelModeIs
		// ChaNoPrivsNeeded
		// NoTonChannel
		// RPL_BANLIST
		// RPL_ENDOFBANLIST
		// Unknownmode
		// NoSuchChannel
		std::vector<IRC::Channel>::iterator receptor = server->getChannelIt(argSplit[0]);
		if (receptor.base() == NULL)
			return setError(ERR_NOSUCHCHANNEL, 1, argSplit[0].c_str());

		if (!receptor->existsUser(user))								// cambiar
			return setError(ERR_NOTONCHANNEL, 1, argSplit[1].c_str()); //revisar

		if(!receptor->isOperator(user))
			return setError(ERR_CHANOPRIVSNEEDED, 1, argSplit[1].c_str()); //revisar
		
		for (int i = 1; i < argSplit[1]; i++)
		{
			if (argSplit[1].at(i) == 'o')
			else if (argSplit[1].at(i) == 'p')
			else if (argSplit[1].at(i) == 's')
			else if (argSplit[1].at(i) == 'i')
			else if (argSplit[1].at(i) == 't')
			else if (argSplit[1].at(i) == 'n')
			else if (argSplit[1].at(i) == 'm')
			else if (argSplit[1].at(i) == 'l')
			else if (argSplit[1].at(i) == 'b')
			else if (argSplit[1].at(i) == 'v')
			else if (argSplit[1].at(i) == 'k')
			else
				return setError(ERR_UMODEUNKWOWNFLAG, 0); // ERR_UMODEUNKWOWN
		}
		
	}
	else if (this->args.at(0) == '&')
	{
		// NeedMoreParams
		// ChannelModeIs
		// ChaNoPrivsNeeded
		// NoTonChannel
		// RPL_BANLIST
		// RPL_ENDOFBANLIST
		// Unknownmode
		// NoSuchChannel
	}
	else
	{
		if (argSplit.size() != 2)
			return setError(ERR_NEEDMOREPARAMS, 1, this->command.c_str());
		
		IRC::User receptor = findUser(server->getUsers(), argSplit[0]);	
		if (receptor == NULL)
			return setError(ERR_NOSUCHNICK, 1, argSplit[0].c_str());
	
		if (!(receptor == user))
			return setError(ERR_USERSDONTMATCH, 0);
		
		// Proteccion transformar +i +s en +is 

		if (argSplit[1].size() > 2)
		{
			for (int i = 1 ; i < argSplit[1].size(); i++)
			{
				if (argSplit[1].at(i) == 'i')
					if(argSplit[1].at(0) == '+')
						user.isInvisible() ? user.changeInvisibility() : return ;
					else if (argSplit[1].at(0) == '-')
						user.isInvisible() ? return : user.changeInvisibility();
				else if (argSplit[1].at(i) == 's')
					if(argSplit[1].at(0) == '+')
						user.isSubscribed() ? user.changeSubscription() : return ;
					else if (argSplit[1].at(0) == '-')
						user.isSubscribed() ? return : user.changeSubscription();
				else if (argSplit[1].at(i) == 'o')
					if(argSplit[1].at(0) == '+')
						return ; 
					else if (argSplit[1].at(0) == '-')
						user.deOp()
				else 
					return setError(ERR_UMODEUNKWOWNFLAG, 0);
			}
		}
		setReply(RPL_UMODEIS, 6, "i: ", user.isInvisible(), "s: ", user.isSubscribed(), "o: ", user.isOp());
	}
}