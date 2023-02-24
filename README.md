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
- https://client01.chat.mibbit.com/


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



[-] Pass
[-] Nick
[-] Username
[-] Privsmg
[-] notice
[-] Join
[-] Part
[-] topic
[-] names
[-] list
[-] mode
[-] quit
[ ] Ping
[ ] Pong




[ ] invite
[ ] oper
[ ] whois
[ ] motd
[ ] kick
[ ] ison
[ ] kill
[ ] who

Lista de prioridades:
- En el caso que no haya operadores de un canal, en la shell, al hacer names el usuario que creo el canal sigue apareciendo como operador
- Cambiar Mode set_rply
- Revisar todo y explicarnoslo

- Control de errores y leaks
- Cambiar arrays a maps para hacer mas eficiente?


nc irc.irc-hispano.org 6667
lsof -t -i tcp:6667 | xargs kill


Refactor .cpp:
-> doble espacio tras includes
-> Orden igual que en el HPP
-> Comentarios secciones
-> Alinear tabs
-> Const en getters y printers
-> This en variables de la clase, no en funciones
-> Void en funciones sin argumentos


/*

pass 12
nick karisti1
user karisti2 0 * :Kepa
join #aaaa,#bbbb


pass 12
nick gpernas1
user gpernas2 0 * :Gonzalo
join #aaaa,#bbbb

pass 12
nick gpernas1
user gpernas2 0 * :Gonzalo

*/


/------
* Mandar PRIVMSG al mismo usuario que lo manda
* Proteger caracteres desconocidos en los canales y usuarios



https://modern.ircdocs.horse/#rplnamreply-353
https://modern.ircdocs.horse/#connection-setup


:aberdeen.chathispano.com 001 karisti1 :Welcome to the IRC-Hispano IRC Network karisti1!karisti2@195.55.210.181
:aberdeen.chathispano.com 002 karisti1 :Your host is aberdeen.chathispano.com, running version InspIRCd-3
:aberdeen.chathispano.com 003 karisti1 :This server was created 10:58:01 Jan 15 2023
:aberdeen.chathispano.com 004 karisti1 aberdeen.chathispano.com InspIRCd-3 BDHIJKNPRSTVchiknorsvwxz CEFHJKMNOQRSTVWbdefijklmnoprstuvxyz :EFHJVbdefjklovxy
:aberdeen.chathispano.com 005 karisti1 AWAYLEN=200 CASEMAPPING=ascii CHANLIMIT=#:20 CHANMODES=be,k,EFHJdfjlxy,CKMNOQRSTWimnprstuz CHANNELLEN=64 CHANTYPES=# ELIST=CMNTU ESILENCE=CcdiNnPpTtx EXCEPTS=e EXTBAN=,CGNSTUXagjmrwz HOSTLEN=64 KEYLEN=32 :are supported by this server
:aberdeen.chathispano.com 005 karisti1 KICKLEN=255 LINELEN=512 MAXLIST=b:200,e:200 MAXTARGETS=1 MODES=6 NAMELEN=128 NETWORK=IRC-Hispano NICKLEN=30 PREFIX=(oVv)@%+ SAFELIST SILENCE=32 STATUSMSG=@%+ TOPICLEN=307 :are supported by this server
:aberdeen.chathispano.com 005 karisti1 USERLEN=10 USERMODES=,,s,BDHIJKNPRSTVchiknorvwxz WATCH=30 WHOX :are supported by this server

Command: '

PROTOCTL NAMESX


CAP REQ MULTI-PREFIX
'

https://hmong.es/wiki/List_of_Internet_Relay_Chat_commands
https://ircv3.net/specs/extensions/capability-negotiation.html
