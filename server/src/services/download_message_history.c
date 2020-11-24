#include "server.h"

//clang -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -g -lsqlite3 main.c bussines_logic_main.c get_contacts.c mx_find_get_contacts_username.c libmx.a cJSON.a count_friends.c mx_my_username.c mx_my_mail.c
//clang -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -g -lsqlite3 main.c bussines_logic_main.c libmx.a cJSON.a download_message_history.c mx_id_chats.c mx_count_chaty.c mx_count_sms.c mx_search_user_1.c mx_search_user_2.c
cJSON *download_message_history(cJSON *j_request, cJSON *j_responce) {

cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "who");

    int num = mx_count_chaty(json_type1->valuestring);  //посчитать колличество чатов //+
    //printf("%d\n", num);
    if(num != 0) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
        cJSON_AddItemToObject(j_responce, "chats count", cJSON_CreateNumber(num));
    }


    if(num > 0) {
        char **id_chats = mx_id_chatss(json_type1->valuestring);  //прмслать массив с айди всех чатов пользователя //+
        int i = 0;
        cJSON *chaty, *info_chat, *id_sms, *time, *sender, *sms;
        chaty = cJSON_CreateArray();
        cJSON_AddItemToObject(j_responce, "chats", chaty);
    
            while(id_chats[i] != NULL) {

                //printf("id_chats %s\n", id_chats[i]);
                cJSON_AddItemToArray(chaty, info_chat = cJSON_CreateObject());
                cJSON_AddItemToObject(info_chat, "chat id", cJSON_CreateString(id_chats[i]));

                    int count_sms = mx_count_sms(id_chats[i]);  //количество сообщений
                    //printf("count_sms %d\n", count_sms);
                    cJSON_AddItemToObject(info_chat, "msg count", cJSON_CreateNumber(count_sms));

                    char *user_1 = mx_search_user_1(id_chats[i]);  //имя юзера
                    char *user_2 = mx_search_user_2(id_chats[i]);	//имя юзера
                    cJSON_AddItemToObject(info_chat, "user 1", cJSON_CreateString(user_1));
                    cJSON_AddItemToObject(info_chat, "user 2", cJSON_CreateString(user_2));

                    id_sms = cJSON_CreateArray();
                    cJSON_AddItemToObject(info_chat, "msg id", id_sms);
                    char **id_smss = id_sms_arr(user_1, user_2, count_sms);
                    int n = 0;

                    while(n != count_sms) {
                      //  printf("aadasasfdsfdsgsgfgdfhdghfghfgfjfjf%d\n", n);
                        if(strcmp(id_smss[0], "-1") == 0)
                            id_smss[0] = NULL;
                    	cJSON_AddItemToObject(id_sms, "msg id", cJSON_CreateString(id_smss[n]));
                    	n++;
                	}

					time = cJSON_CreateArray();
                    cJSON_AddItemToObject(info_chat, "time", time);
                 	int *get_time = mx_get_time(user_1, user_2, count_sms);
                    n = 0;

                    while(n != count_sms) {
                        cJSON_AddItemToObject(time, "time", cJSON_CreateNumber(get_time[n]));
                        n++;
                    }

                sender = cJSON_CreateArray();
                char **get_who = mx_get_who(user_1, user_2, count_sms);
                n = 0;
                while (n != count_sms) {
                    if (strcmp(get_who[0], "-1") == 0)
                        get_who[0] = NULL;
                    cJSON_AddItemToArray(sender, cJSON_CreateString(get_who[n]));
                    n++;
                }
                cJSON_AddItemToObject(info_chat, "sender", sender);

                 sms = cJSON_CreateArray();
                 cJSON_AddItemToObject(info_chat, "msg", sms);
                 char **get_sms = mx_get_sms(user_1, user_2, count_sms);
                 n = 0;

                  while(n != count_sms) {
                        if(strcmp(get_sms[0], "-1") == 0)
                            get_sms[0] = NULL;
                        cJSON_AddItemToObject(sms, "msg", cJSON_CreateString(get_sms[n]));
                        n++;
                    }
                i++;
            }
        }

    // char *jdata = cJSON_Print(j_responce);
    // printf("%s\n", jdata);
//    
    if(num == 0)
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}



