CC = g++
CFLAGS = -Wall

all: udp_client udp_server

udp_client: udp_client.cpp
	$(CC) $(CFLAGS) -o udp_client udp_client.cpp

udp_server: udp_server.cpp
	$(CC) $(CFLAGS) -o udp_server udp_server.cpp

clean:
	rm -f udp_client udp_server
