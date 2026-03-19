#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "DENSocket.h"

static int work = 1;
static int end = 2;


//prime finding methods

static bool isPrime(int number){//check if a number is prime
    
    bool prime = true;
    if (number < 2){
        prime = false;
    }else{
        int num = 2;
        while (num < number -1 && prime){
            if(number % num == 0){
                prime = false;
            }
            num++;
        }
    }
    return prime;
}

static int FindPrimeCount(int start, int end){//count primes in a range
    int count = 0;
    int current = start;
    while(current <= end){
        if(isPrime(current)){
            count++;
        }
        current++;
    }
    return count;
}


int main(int argc, char** argv){
    //take in the port and head
    if (argc != 3) {
        printf("Wrong Command\n");
    return 1;
    }

    std::string host = argv[1];
    int port = atoi(argv[2]); //String to int

    DENSocket* s = new DENSocket(host, port);//set up socket 
    printf("Node connected to Head at %s:%d\n", host.c_str(), port);

    bool running = true;
    while (running){
        int cmd = s->readInt();
        if (cmd == work){

            //get staring and ending rnage
            int start = s->readInt();
            int end = s->readInt();

            printf("Working on range [%d - %d]\n", start, end);

            int result = FindPrimeCount(start, end);

            s->writeInt(result);//give result 

        }else if (cmd == end){
            printf("Ending Program\n");
            running = false;

        }else{
            printf("Unknown Command Received\n");

        }
      
    }
    s->closeSocket();//close the socket
    return 0;//end program

}