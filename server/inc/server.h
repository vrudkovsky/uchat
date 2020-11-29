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
char *in_search_mail(char *username); 

//download_message_history
cJSON *download_message_history(cJSON *j_request, cJSON *j_responce);
int mx_count_chats(char *username);
int *mx_id_chatss(char *who, int num);
int mx_count_sms(int chat_id);
char *mx_search_interlocutor(int id_chat, char *username);
int *get_msgs_ids(int chat_id, int count_sms);
int *mx_get_time(int chat_id, int count_sms);
int *mx_is_msg_owner(char *username, int count_sms, int chat_id);
char **mx_get_who(char *who, char *whom, int count_sms);
char **mx_get_msg_text(int chat_id, int count_sms);
void mx_ceate_username_password_login(void);

//get_chat
cJSON *get_chat(cJSON *j_request, cJSON *j_responce);
bool check_chat_by_id(int chat_id);

//create chat
cJSON *create_new_chat(cJSON *j_request, cJSON *j_responce);
int mx_find_chat_with_contact(char *who, char *whom);
int mx_create_new_chat(char *who, char *whom);
int mx_create_new_db_chat(char *id, char *username1, char *username2);


void mx_delete_contactt(void);
void mx_create_new_table(void);

cJSON *updates_main(cJSON *j_request, cJSON *j_responce);
int insert_new_msg(char *who, char *whom, char *text, int created_at, int chat_id);
char **mx_id_chats(char *who);
int count_sms_give(char *username);
cJSON *send_msg(cJSON *j_request, cJSON *j_responce);
//int mx_create_new_db_chat(void);


//new_sms and new chats
int count_id_new_chats(char *username);
int count_id_new_sms(char *username);
int *new_update_msgs_info(char *who, int num);
int *new_update_chats_info(char *who, int num);
char *find_message_by_id(int id_message);
char *find_username_by_id(int user_id); 
bool change_chat_status(int chat_id);
bool change_msg_status(int msg_id);
//delete sms
bool delete_sms(int id_sms);
cJSON *mx_delete_sms(cJSON *j_request, cJSON *j_responce);

//update sms
bool update_sms(int id_sms, char *text_sms);
cJSON *mx_update_sms(cJSON *j_request, cJSON *j_responce);

#endif


