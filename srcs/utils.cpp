/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:29:12 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/26 19:18:53 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

/*
	- Splits the "str" string by a given "delim" delimiter.
	- You can set a max split amount with "count".
*/
std::vector<std::string>	splitString(std::string str, std::string delim, int count)
{
	size_t pos = 0;
	std::vector<std::string> tokens;
	while (count != 0 && (pos = str.find(delim)) != std::string::npos)
	{
		if (!str.substr(0, pos).empty())
		{
			tokens.push_back(str.substr(0, pos));
			count--;
		}
		str.erase(0, pos + 1);
	}
	
	tokens.push_back(str);

	std::cout << ">>> splitString: [";
	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++)
	{
		std::cout << "'" << *it << "'";
		if (it + 1 != tokens.end())
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
	
	return tokens;
}

bool socketKiller = false;

void sig_handle(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		socketKiller = true;
	}
}

void catchSignal(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sig_handle;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

std::string		pingGenerator(const int &size) {
	std::string	nums = "0123456789";
	std::string	randstr;
	srand(std::time(NULL));

	for (int i = 0; i < size; i++)
		randstr += nums[rand() % nums.length()];
	return randstr;
}
