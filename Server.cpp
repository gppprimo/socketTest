//
//  Server.cpp
//  BerkeleySockets
//
//  Created by Giuseppe Primo on 17/05/2018.
//  Copyright © 2018 Giuseppe Primo. All rights reserved.
//

#include "Server.hpp"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int main(){
    
//  creating a new socket with a local address (DOMAIN), transport type (SOCK_STREAM -> TCP), protocol (0 -> IP) and saving the identifier
    int idServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (idServerSocket < 0){
        cerr<<"Error: socket not created";
        return -1;
    } else {
        cout<<"Server: socket created with id: " << idServerSocket << endl;
    }
    
//    creating the structure to complete the binding
    struct sockaddr_in serverSocketAddr;
    
    serverSocketAddr.sin_family = AF_INET;  // internet address
    serverSocketAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // binding on any available interfaces
    serverSocketAddr.sin_port = htons(58988);
    

//    binding the socket to a socket address structure (i.e IP and Port)

    if(bind(idServerSocket, (struct sockaddr *) &serverSocketAddr, sizeof(serverSocketAddr)) < 0)
        cerr<<"Error: binding - error code: " << errno << endl;
    else
        cout<<"Server: bind" << endl;

    // listening on socket with queue lenght = 3
    if(listen(idServerSocket, 3) < 0)
        cerr<<"Error: listening - error code: "<<errno;
    else
        cout<<"Server: listening on ip: "<< serverSocketAddr.sin_addr.s_addr << " and port: " << ntohs(serverSocketAddr.sin_port) << endl;

    while(true){
        int newServerSocketId;    // new socket descriptor mapped to the first pending connection in the socket queue after calling "accept". A copy of the existing socket will be saved
        if((newServerSocketId = accept(idServerSocket, (struct sockaddr *) &serverSocketAddr, (socklen_t *) &(serverSocketAddr)  )) < 0 )
            cerr<<"Error: accept - error code: "<<errno;
        else
            cout<<"Server: accept" << endl << "new socketId: " << newServerSocketId << endl;
        
        char buffer[2048] = {0};    // buffer to store received messages
        if(recv(newServerSocketId, buffer, 2048, 0) < 0)
            cerr<<"Error: receiving message - error code: " << errno;
        else{
            cout << "Message received: " << buffer << endl;
            shutdown(newServerSocketId, SHUT_RD);
            cout << "Connection closed" << endl << endl;
        }
    }
    return 0;
}
