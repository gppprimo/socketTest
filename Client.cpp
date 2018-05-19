//
//  Client.cpp
//  BerkeleySockets
//
//  Created by Giuseppe Primo on 17/05/2018.
//  Copyright © 2018 Giuseppe Primo. All rights reserved.
//

#include "Client.hpp"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int main(){
 
    //  creating a new socket with a local address (DOMAIN), transport type (SOCK_STREAM -> TCP), protocol (0 -> IP) and saving the identifier
    int idClientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (idClientSocket < 0)
        cerr<<"Error: socket not created";
    else
        cout<<"Server: socket created with id: " << idClientSocket << endl;
    
    //    creating the structure to complete the binding
    struct sockaddr_in clientSocketAddr;
    clientSocketAddr.sin_family = AF_INET;
    clientSocketAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientSocketAddr.sin_port = htons(58988);
    
    // request a connection to the server
    cout<<"Client: request on ip: "<< clientSocketAddr.sin_addr.s_addr << " and port: " << ntohs(clientSocketAddr.sin_port) << endl;
    
    if((connect(idClientSocket, (struct sockaddr *) &clientSocketAddr, sizeof(clientSocketAddr))) < 0)
        cerr << "Error: connect - error code: " << errno << endl;
    else
        cout << "Client: connect" << endl;
    
    // client business logic
    std::string message;
    char buffer[200];
    
    cout << "Please, insert message to the server..." << endl << endl;
    
    cin.getline(buffer, sizeof(buffer));
    
    cout << "Sending message..." << endl;
    
    send(idClientSocket, buffer, sizeof(message), 0);
    
    cout << "Message sent" << endl;
    
    return 0;
}
