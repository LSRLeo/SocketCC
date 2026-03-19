// compile: g++ server.cc DENSocket.cc DENServerSocket.cc -o server
#include <stdio.h>
#include "DENSocket.h"
#include "DENServerSocket.h"


int main() {
  int port = 7000;
  DENServerSocket* ss = new DENServerSocket(port);

  printf("Server waiting for clients\n");
  DENSocket* s = ss->acceptConnection();
  printf("Client connected\n");

  int x = s->readInt();
  printf("Server read %d\n", x);
  int y = x*2;
  s->writeInt(y);

  s->closeSocket();

  return 0;
}