


edit : main.o net_socket.o net_tcp.o
	g++ -g main.o net_socket.o net_tcp.o -o main

main.o : net_tcp.h main.cpp
	g++ -g -c main.cpp
net_socket.o : net_socket.h net_socket.cpp
	g++ -g -c net_socket.cpp
net_tcp.o : net_socket.h net_tcp.h net_tcp.cpp
	g++ -g -c net_tcp.cpp



.PHONY : clean

clean : 
	rm -rf *.o *.gch main
