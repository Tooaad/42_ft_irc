#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>


namespace IRC {
	class Client {
		private:
			sockaddr_in	address;
			socklen_t	size;
			int			cSocket;

		public:
			Client();
			Client(int sSocket);
			Client(const Client& other);
			~Client();
			Client& operator= (const Client& other);

			void		clientSetup() const;
			sockaddr_in	getClientAddress() const;
			socklen_t	getClientSize() const;
			int			getSocket() const;
	};
}
