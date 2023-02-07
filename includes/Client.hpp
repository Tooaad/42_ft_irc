/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:08 by karisti-          #+#    #+#             */
/*   Updated: 2023/02/07 13:38:58 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>


namespace IRC
{
	class Client
	{
		private:
			sockaddr_in		address;
			int				cSocket;
			socklen_t		size;

		public:
			Client();
			Client(int serverSocket);
			Client(const Client& other);
			~Client();
			Client& operator= (const Client& other);

			/* -- Getters -- */
			sockaddr_in		getAddress(void) const;
			int				getSocket(void) const;
			socklen_t		getSize(void) const;

			/* -- Member functions -- */
			void			setup(void);
	};
}
