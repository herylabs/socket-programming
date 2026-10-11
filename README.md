# socket-programming
Learning about socket programming in C

`nc -l -p 6969` starts Netcat in listening (server mode) mode on local TCP port `6969`.

- `nc` runs Netcat, a command-line tool for network connections.
- `-l` tells Netcat to listen for an incoming connection.
- `-p 6969` selects port `6969`.

Run this command before starting the client program. When the client connects to `127.0.0.1:6969`, Netcat displays the data it sends, such as `Bonjour`.

Some Netcat versions use `nc -l 6969` instead of `nc -l -p 6969`.



