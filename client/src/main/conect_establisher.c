#include "client.h"

void connection_establisher(unsigned short port, char *ip_address) {
    short sockfd;
    struct sockaddr_in servaddr;

    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        mx_printerr("Error: client socket creation failed\n"); 
        exit(1); 
    } 
    else
        mx_printstr("Success: client socket created successfully\n"); 
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(ip_address); 
    servaddr.sin_port = htons(port); 

    // connect the client socket to server socket 
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) { 
        mx_printerr("Error: connection to the server failed\n");
        exit(1); 
    } 
    else
        mx_printstr("Success: connection to the server established\n"); 
    main_data.sock_fd = sockfd;
}
