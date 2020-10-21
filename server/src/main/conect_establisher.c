#include "server.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void connection_establisher(unsigned short port) {
    char hostbuffer[256];
    int hostname; 
    int socket_desc, client_sock, c;
    struct hostent *host_entry;
    struct sockaddr_in server, client;

    hostname = gethostname(hostbuffer, sizeof(hostbuffer)); 
    host_entry = gethostbyname(hostbuffer);
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
        exit(1);
    }
    server.sin_family = AF_INET;
    inet_aton(host_entry->h_addr_list[0], &server.sin_addr);
    server.sin_port = htons(port);
    int bind_connect = bind(socket_desc, (struct sockaddr *)&server, sizeof(server));
    if (bind_connect < 0) {
        perror("bind failed. Error");
        exit(1);
    }
    listen(socket_desc , 3);
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    pthread_t thread_id;
    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ) {
        puts("Connection accepted");
        if (pthread_create(&thread_id, NULL, connection_handler, (void*) &client_sock) < 0)
            perror("could not create thread");
        puts("Session with client is active");
    }
    if (client_sock < 0)
        perror("accept failed");
}
