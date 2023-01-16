# ft_irc

Notion: https://comet-sycamore-801.notion.site/Team-Home-e792cf6da5824c139b21268e9f21ae64

# How to use it?

Server side:
```
make test
```

Client side:
```
nc -NC 127.0.0.1 6667
```
-> Shall output "Amazing" on server side
-> Usable with ::1 as IPv6
-> Usable with localhost
-> Usable with network ip

-N : close fd when using ctrl+d

//nc -C -N ircnet.clue.be 6667