#include "server.h"

void *connection_handler(void *socket_desc) {
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];

    while((read_size = recv(sock, client_message, 2000, 0)) > 0 ) {
        cJSON *j_request = cJSON_CreateObject();
        cJSON *j_responce= cJSON_CreateObject();
        client_message[read_size] = '\0';
        printf("recive <-\n%s\n", client_message);
        j_request = cJSON_Parse(client_message);
        bussines_logic_main(j_request, j_responce);
        send_responce(sock, j_responce);
        memset(client_message, 0, 2000);        
        cJSON_Delete(j_request);
        cJSON_Delete(j_responce);
    }
    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }
    if (read_size == -1) {
        perror("Recv failed");
    }
    return 0;
}
