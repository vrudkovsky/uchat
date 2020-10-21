#ifndef SERVER_H
#define SERVER_H

#include "libmx.h"
#include "cJSON.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <netdb.h>
#include <errno.h>
#include <pthread.h>
#include <ifaddrs.h>
#include <sqlite3.h>

void start_error(int argc, char **argv);
void connection_establisher(unsigned short port);
void *connection_handler(void *socket_desc);
cJSON *bussines_logic_main(cJSON *j_request, cJSON *j_responce);
cJSON *login_user(cJSON *j_request, cJSON *j_responce);
cJSON *register_user(cJSON *j_request, cJSON *j_responce);
void send_responce(int sock, cJSON *j_responce);

bool mx_create_username_password_login(char *str_1, char *str_2, char *str_3);
bool mx_find_email(char *email);
bool mx_find_username(char *username);
bool mx_find_password(char *pass);

#endif
