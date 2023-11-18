CC = g++
CFLAGS = -Wall

all: tcp_client tcp_server

tcp_client: tcp_client.cpp
	$(CC) $(CFLAGS) -o tcp_client tcp_client.cpp

tcp_server: tcp_server.cpp
	$(CC) $(CFLAGS) -o tcp_server tcp_server.cpp

clean:
	rm -f tcp_client tcp_server
