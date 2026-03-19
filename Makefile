head: head.o DENSocket.o DENServerSocket.o
	g++ -fopenmp head.o DENSocket.o DENServerSocket.o -o head

node: node.o DENSocket.o
	g++ -fopenmp node.o DENSocket.o -o node

head.o: head.cc DENServerSocket.h DENSocket.h
	g++ -fopenmp head.cc -c

node.o: node.cc DENSocket.h
	g++ -fopenmp node.cc -c

DENSocket.o: DENSocket.cc DENSocket.h
	g++ -fopenmp DENSocket.cc -c

DENServerSocket.o: DENServerSocket.cc DENServerSocket.h DENSocket.h
	g++ -fopenmp DENServerSocket.cc -c

clean:
	rm -f *.o
	rm -f head node