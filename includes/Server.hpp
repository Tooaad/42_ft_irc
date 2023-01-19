#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h> // fcntl
#include <sys/event.h> // kqueue


namespace IRC {
	class Server {
		private:
			int				sSocket;
			int				kq;
			struct kevent	change_event[4];
			struct kevent	event[4];



// //			◦ If host, port_network and password_network aren’t given, you must create a new IRC network
// //			◦ host is the hostname on which IRC must connect to join a already existing network
// 			std::string		hostname;
// //			◦ port_network is the server port on which IRC must connect on host
// 			int				port_network;
// //			◦ password_network is the password needed to connect on host
// 			std::string		pw_network;
// //			◦ port is the port number on which your server will accept incoming connections.
// 			int				port;
// //			◦ password is the password needed by any IRC client who wants to connect to your server.
// 			std::string		password;


		public:
			Server();
			Server(const Server& other);
			Server& operator=(const Server& other);
			~Server();

			int createNetwork(std::string *args);
			void connectNetwork(std::string *args);
			int getSocket(void) const;
			int getKq(void);
			struct kevent*	getEvent(void);
			struct kevent*	getChgEvent(void);
	};
}
