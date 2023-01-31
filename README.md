# ft_irc

## RFC-IRC PROTOCOL
- https://www.ietf.org/rfc/rfc1459.txt
- https://www.rfc-es.org/rfc/rfc1459-es.txt
- https://modern.ircdocs.horse/#client-to-server

## IRC Clients using on terminal is kinda ugly
- https://kiwiirc.com/              (Online)
- https://www.mirc.com/             (Online)
- https://bitchx.sourceforge.net/
- http://www.instantbird.com/


## Info
- TCP/IP Protocol in C++: https://lenngro.github.io/how-to/2021/01/05/Simple-TCPIP-Server-Cpp/
- TCP/IP v4 example in C: https://www.ibm.com/docs/en/zos/2.1.0?topic=applications-example-ipv4-tcp-server-program
- In-Out events (Poll/Select/Kqueue): https://nima101.github.io/io_multiplexing 
- Non-Blocking fd C++: https://stackoverflow.com/questions/5616092/non-blocking-call-for-reading-descriptor
- Non-Blocking fd C++ extended version: https://www.linuxtoday.com/blog/blocking-and-non-blocking-i-0/
- Sockets: https://beej.us/guide/bgnet/pdf/bgnet_usl_c_1.pdf (Pag 60)

No bloqueante
- https://www.linuxtoday.com/blog/blocking-and-non-blocking-i-0/
- https://linux.die.net/man/7/socket
- https://man7.org/linux/man-pages/man2/fcntl.2.html

Kqueue
- https://www.youtube.com/watch?v=Y6pFtgRdUts
- https://nima101.github.io/io_multiplexing
- http://eradman.com/posts/kqueue-tcp.html
- https://wiki.netbsd.org/tutorials/kqueue_tutorial/
- [bueno] https://dev.to/frevib/a-tcp-server-with-kqueue-527



## CONCEPTS
* BSD Sockets
* Receive commands via recv()
* Check Alive status with PINGS that must be responded with /PONG time()
* Concurrency run() livelock
* Multithreading -> main
                    send() [OPTIONAL]
                    receive()
* Serializacion

# Project Examples
- https://www.nongnu.org/cpirc/
- https://opensource.com/life/16/6/irc-quickstart-guide
- https://opensource.com/life/16/6/irc
- https://oramind.com/tutorial-how-to-make-an-irc-server-connection/
- https://se.inf.ethz.ch/student_projects/fabian_gremper/Report.pdf

- TPC Server Linux https://www.youtube.com/watch?v=cNdlrbZSkyQ
- TPC Server Mac https://www.youtube.com/watch?v=F3iIGUiW27Q

[+] Join
[+] Part
[+] topic

[-] Pass
[-] Nick
[-] Username
[-] Privsmg

[ ] list
[ ] names
[ ] invite
[ ] Ping
[ ] Pong
[ ] quit
[ ] mode
[ ] oper
[ ] 
[ ]

[ ] whois
[ ] motd
[ ] kick
[ ] ison
[ ] squit
[ ] kill
[ ] who


nc irc.irc-hispano.org 6667


/*
> join #jeje
	:karisti1!karisti1@0G6.n4M.2Cld1O.virtual JOIN :#jeje
	:glencoe.chathispano.com 332 karisti1 #jeje :teeeeeeeeeest
	:glencoe.chathispano.com 333 karisti1 #jeje Guest53 :1675104783
	:glencoe.chathispano.com 353 karisti1 = #jeje :karisti1 @Guest53
	:glencoe.chathispano.com 366 karisti1 #jeje :End of /NAMES list.


> part #jeje
	:karisti1!karisti1@0G6.n4M.2Cld1O.virtual PART :#jeje
*/
/*
> join #jeje
	:karisti!Kepa@127.0.0.1 JOIN :#jeje
	:127.0.0.1 331 karisti #jeje :No topic is set
	:127.0.0.1 353 karisti = #jeje :@karisti
	:127.0.0.1 366 karisti #jeje :End of /NAMES list.
	
> part #jeje
	:karisti!Kepa@127.0.0.1 PART #jeje :

	:karisti!Kepa@127.0.0.1 PART #jeje :
	:Nick!user@hostname
*/
