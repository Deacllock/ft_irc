# ft_irc

Notion: https://comet-sycamore-801.notion.site/Team-Home-e792cf6da5824c139b21268e9f21ae64

# How to use it?

Server side:
```
make test
```

Client side:
```
nc -CN 127.0.0.1 6667
```
-> Usable with ::1 as IPv6
-> Usable with localhost
-> Usable with network ip

-N : close fd when using ctrl+d
-C : enter \r\n automatically when enter is pressed

Otherwise
```
irssi -c localhost -w pwd -p 6667
```

//nc -C -N ircnet.clue.be 6667