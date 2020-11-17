#include "server.h"

//clang -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -g -lsqlite3 main.c bussines_logic_main.c get_contacts.c mx_find_get_contacts_username.c libmx.a cJSON.a count_friends.c mx_my_username.c mx_my_mail.c
//clang -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -g -lsqlite3 main.c bussines_logic_main.c libmx.a cJSON.a download_message_history.c mx_id_chats.c mx_count_chaty.c mx_count_sms.c mx_search_user_1.c mx_search_user_2.c
cJSON *create_chat(cJSON *j_request, cJSON *j_responce) {

cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "who");
cJSON *json_type2 = cJSON_GetObjectItemCaseSensitive(j_request, "whom");

    int num = mx_create_chat(json_type1->valuestring, json_type2->valuestring);  //посчитать колличество чатов //+
    //printf("%d\n", num);
    if(num != 0) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
        cJSON_AddItemToObject(j_responce, "id_chat", cJSON_CreateNumber(num));
    }

    // char *jdata = cJSON_Print(j_responce);
    // printf("%s\n", jdata);
//    
    if(num == 0)
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}



