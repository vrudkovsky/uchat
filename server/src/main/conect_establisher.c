#include "server.h"
#include <sys/stat.h>

void connection_establisher(unsigned short port) {
    char hostbuffer[256];
    int hostname; 
    int socket_desc, client_sock, c;
    struct hostent *host_entry;
    struct sockaddr_in server, client;
    pid_t process_id = 0;
    pid_t sid = 0;

    process_id = fork();
    if (process_id < 0) {
        printf("fork failed!\n");
        exit(1);
    }
    if (process_id > 0) {
        printf("process_id of child process %d \n", process_id);
        exit(0);
    }
    umask(0);
    sid = setsid();
    if(sid < 0)
        exit(1);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
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
