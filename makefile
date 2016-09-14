
OBJECTS = main.o net_socket.o net_tcp.o #net_ip.o


edit : $(OBJECTS)
	g++ -o main $(OBJECTS)

main.o : net_tcp.h #net_ip.h

net_socket.o : net_socket.h

net_tcp.o : net_socket.h net_tcp.h

#net_ip.o : net_ip.h net_socket.h

.PHONY : clean

clean : 
	-rm -rf *.o *.gch main ./src/*
