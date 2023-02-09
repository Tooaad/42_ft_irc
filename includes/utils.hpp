/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:31:29 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/07 20:06:43 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <csignal>
#include <signal.h>

extern bool socketKiller;
// TODO: delete?
// std::string					trimEndl(std::string str);
std::vector<std::string>	splitString(std::string str, std::string delim, int count = -1);
void catchSignal(void);
void sig_handle(int sig);