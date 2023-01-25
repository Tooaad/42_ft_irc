/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:29:12 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/25 10:22:30 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

std::string	trimEndl(std::string str)
{
	std::string::iterator found = std::find(str.begin(), str.end(), '\n');
	
	if (found != str.end())
		str.erase(found);

	return str;
}

/*
	- Splits the "str" string by a given "delim" delimiter.
	- You can set a max split amount with "count".
*/
std::vector<std::string> splitString(std::string str, std::string delim, int count)
{
	size_t pos = 0;
	std::vector<std::string> tokens;
	while (count != 0 && (pos = str.find(delim)) != std::string::npos) {
		tokens.push_back(str.substr(0, pos));
		// TODO: remove
		// std::cout << tokens.back() << std::endl;
		str.erase(0, pos + 1);
		count--;
	}
	tokens.push_back(str);
	// TODO: remove
	// std::cout << tokens.back() << std::endl;
	return tokens;
}
