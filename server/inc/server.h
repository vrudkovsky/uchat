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
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <pthread.h>
#include <ifaddrs.h>
#include <sqlite3.h>


//server connect
void start_error(int argc, char **argv);
void connection_establisher(unsigned short port);
void *connection_handler(void *socket_desc);
void send_responce(int sock, cJSON *j_responce);

//boss server
cJSON * bussines_logic_main(cJSON *j_request, cJSON *j_responce);

//boss server - wowk function
cJSON *login_user(cJSON *j_request, cJSON *j_responce);
cJSON *register_user(cJSON *j_request, cJSON *j_responce);
cJSON *find_user(cJSON *j_request, cJSON *j_responce);
cJSON *get_contacts(cJSON *j_request, cJSON *j_responce);
cJSON *add_contact(cJSON *j_request, cJSON *j_responce);
cJSON *delete_contact(cJSON *j_request, cJSON *j_responce);

//db function
bool mx_create_username_password_login(char *str_1, char *str_2, char *str_3);
bool mx_find_email(char *email);
bool mx_find_username(char *username);
bool mx_find_password(char *pass, char *login);
bool in_contact_list(char *who, char *whom);
bool mx_add_contact(char *who, char *whom);
bool mx_add_contact(char *who, char *whom);
bool mx_find_get_contacts_username(char *who);
bool mx_delete_contact(char *who, char *whom);
char **mx_my_username(char *who);
char **mx_my_mail(char *who);
int count_friends(char *who);
const char *in_search_mail(char *username); 

//download_message_history
cJSON *download_message_history(cJSON *j_request, cJSON *j_responce);
int mx_count_sms(char *id_chat);
char *mx_search_user_1(char *id_chat);
char *mx_search_user_2(char *id_chat);
int *mx_get_time(char *who, char *whom, int count_sms);
char **mx_get_who(char *who, char *whom, int count_sms);
char **mx_get_sms(char *who, char *whom, int count_sms);
void mx_ceate_username_password_login(void);
int mx_count_chaty(char *username);
char **mx_id_chatss(char *who);
int mx_count_chaty(char *username);
char **id_sms_arr(char *who, char *whom, int count_sms);

//create chat
cJSON *create_chat(cJSON *j_request, cJSON *j_responce);



void mx_delete_contactt(void);
void mx_create_new_table(void);

int mx_create_chat(const char *username_1, const char *username_2);
cJSON *create_chat(cJSON *j_request, cJSON *j_responce);

int mx_create_new_db_chat(char *id, char *username1, char *username2);

cJSON *sms(cJSON *j_request, cJSON *j_responce);
char *create_sms(char *who, char *whom, char *text, char *created_at);
char **mx_id_chats(char *who);
int count_sms_give(char *username);
cJSON *sms(cJSON *j_request, cJSON *j_responce);
cJSON *smsq(cJSON *j_request, cJSON *j_responce);
//int mx_create_new_db_chat(void);
#endif


