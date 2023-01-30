# ft_irc

# How to use it?

## Server side:
```
make test
```

## Client side:
```
nc -NC 127.0.0.1 6667
```
-N : close fd when using ctrl+d
-C : add crlf when enter is pressed

```
irssi -c localhost -p 6667 -w pwd -n test
```

-> Usable with ::1 as IPv6
-> Usable with localhost
-> Usable with network ip

## List of handled commands
- INVITE
- JOIN
- LIST
- MODE
  + User (o)
  + Channel (i, b, o, k, l)
- NAMES
- PART
- TOPIC
- NICK
- PASS
- PING
- PONG
- USER
- PRIVMSG
- DIE
- KICK
- KILL
- OPER
