#include "server.h"

void send_responce(int sock, cJSON *j_responce) {
    char *j_data = cJSON_Print(j_responce);
    printf("sent ->\n%s\n", j_data);
    write(sock, j_data, strlen(j_data));
    free(j_data);
}
