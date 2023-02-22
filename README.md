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
- Revisar Modes + Derivados Modes (PrivMSG/List/Channels)
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

TODO: @+ en names, usuario puede ser operador y administrador a la vez



/*
con contraseña:

list #viva42
:edinburgh.chathispano.com 321 kepa Channel :Users Name
:edinburgh.chathispano.com 322 kepa #viva42 1 :[+knt <key>] atsdasd asd asd
:edinburgh.chathispano.com 323 kepa :End of channel list.


sin pass:
list #viva42
:edinburgh.chathispano.com 321 kepa Channel :Users Name
:edinburgh.chathispano.com 322 kepa #viva42 2 :[+knt adasdads] atsdasd asd asd
:edinburgh.chathispano.com 323 kepa :End of channel list.

<channel> <client count> :<topic>

321     RPL_LISTSTART
                        "Channel :Users  Name"
322     RPL_LIST
                        "<channel> <# visible> :<topic>"
323     RPL_LISTEND
                        ":End of /LIST"
*/


/*

pass 12
nick karisti
user karisti 0 * :Kepa
join #aaaa,#bbbb


pass 12
nick gpernas
user gpernas 0 * :Gonzalo
join #aaaa,#bbbb

*/

pass 12
nick karisti1
user karisti2 0 * :Kepa

:edinburgh.chathispano.com 396 karisti1 Mv6.j18.j49ElA.virtual :is now your displayed host
:karisti1!karisti2@Mv6.j18.j49ElA.virtual JOIN :#test


/------
* Mandar PRIVMSG al mismo usuario que lo manda
* Proteger caracteres desconocidos en los canales y usuarios

:karisti PRIVMSG #bird :hola gonzalo
:karisti PRIVMSG #bird :hola privmsg


:karisti!karisti@Mv6.j18.j49ElA.virtual JOIN :#test


pass 12
nick gpernas1
user gpernas2 0 * :Gonzalo

:gpernas1!gpernas2@10.11.14.6 JOIN :#test
Host1: c1r14s6.42madrid.com connected on port 56925



:karisti!karisti1@c1r14s6.42madrid.com JOIN :#test
:karisti!karisti1@c1r14s6.42madrid.com JOIN :#abc
:totoadd!Tototoadd1@c1r14s4.42madrid.com JOIN :#test


:glencoe.chathispano.com 396 karisti Mv6.j18.j49ElA.virtual :is now your displayed host
:toad!toad@Kb5.j18.j49ElA.virtual JOIN :#prueba (mio)

:edinburgh.chathispano.com 396 toad Kb5.j18.j49ElA.virtual :is now your displayed host
:toad!toad@Kb5.j18.j49ElA.virtual JOIN :#prueba (gonzalo)


-------

:toadddd!toadddd@c1r14s4.42madrid.com JOIN :#test
:toadddd!toadddd@c1r14s4.42madrid.com JOIN :#test

https://modern.ircdocs.horse/#rplnamreply-353
