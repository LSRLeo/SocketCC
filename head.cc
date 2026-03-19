#include <stdio.h>
#include "DENServerSocket.h"
#include "DENSocket.h"


static int work = 1;
static int end = 2;

int main(int argc, char** argv){
    // int start = 1000;
    // int finish = 1000000;

    // int port = 4000;
    // int expectedNode = 4;
   
    int start;
    int finish;
    int expectedNode;
    int port;

    if (argc == 5) {
        start = atoi(argv[1]);
        finish = atoi(argv[2]);
        expectedNode = atoi(argv[3]);
        port = atoi(argv[4]);

    } else if (argc != 1) {
        printf("Usage: ./head 1000 1000000 3 4000\n");
    }

    DENServerSocket* ss = new DENServerSocket(port);
    printf("Head started, waiting for %d nodes on port %d...\n", expectedNode, port);

    //accept nodes
    DENSocket** nodes = new DENSocket*[expectedNode];

     

    for (int i = 0; i < expectedNode; i++) {
        nodes[i] = ss->acceptConnection(); // blocks
        printf("Node connected (%d/%d)\n", i + 1, expectedNode);
    }

    printf("All nodes connected\n");

    //split work
    int total = finish - start + 1;
    int* rangeStart = new int[expectedNode];
    int* rangeEnd = new int[expectedNode];

    for (int i = 0; i < expectedNode; i++) {
        rangeStart[i]  = start + (i * total) / expectedNode;
        rangeEnd[i] = start + ((i + 1) * total) / expectedNode - 1;
        printf("Assigned Node %d range [%d - %d]\n", i, rangeStart[i] + 1, rangeEnd[i] + 1);
    }


    
    //USE openMp to set up number of Threads to match 



    int totalPrimes = 0; //later using progma to insure synchronization
    #pragma omp parallel for reduction(+:totalPrimes)
    for (int i = 0; i <expectedNode; i++) {
        nodes[i]->writeInt(work);
        nodes[i]->writeInt(rangeStart[i]);
        nodes[i]->writeInt(rangeEnd[i]);

        int localPrime = nodes[i]->readInt(); // blocks waiting for node response
        printf("Node %d Range %d to %d : %d\n", i, rangeStart[i], rangeEnd[i], localPrime);

        totalPrimes += localPrime;
    }

    printf("FINAL TOTAL primes = %d\n", totalPrimes);


    //stop the nodes
    for (int i = 0; i < expectedNode; i++) {
        nodes[i]->writeInt(end);
        nodes[i]->closeSocket();
    }
    ss->closeSocket();

    return 0;



}