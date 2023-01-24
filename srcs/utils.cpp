/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:29:12 by karisti-          #+#    #+#             */
/*   Updated: 2023/01/24 14:36:13 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

std::string	trimEndl(std::string str)
{
	std::size_t found = str.find_last_not_of('\n');
	
	if (found != std::string::npos)
		str.erase(found + 1);

	return str;
}

std::vector<std::string> splitString(std::string str, std::string delim)
{
	size_t pos = 0;
	std::vector<std::string> tokens;
	while ((pos = str.find(delim)) != std::string::npos) {
		tokens.push_back(str.substr(0, pos));
		std::cout << tokens.back() << std::endl;
		str.erase(0, pos + 1);
	}
	tokens.push_back(str.substr(0, pos));
	std::cout << tokens.back() << std::endl;
	return tokens;
}
