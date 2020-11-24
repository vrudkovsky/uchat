#include "server.h"

//clang -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -g -lsqlite3 main.c bussines_logic_main.c get_contacts.c mx_find_get_contacts_username.c libmx.a cJSON.a count_friends.c mx_my_username.c mx_my_mail.c
//clang -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -g -lsqlite3 main.c bussines_logic_main.c libmx.a cJSON.a download_message_history.c mx_id_chats.c mx_count_chaty.c mx_count_sms.c mx_search_user_1.c mx_search_user_2.c
cJSON *smsq(cJSON *j_request, cJSON *j_responce) {
  
cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "who"); //string
cJSON *json_type2 = cJSON_GetObjectItemCaseSensitive(j_request, "whom");  //string
cJSON *json_type3 = cJSON_GetObjectItemCaseSensitive(j_request, "msg");  //string
cJSON *json_type4 = cJSON_GetObjectItemCaseSensitive(j_request, "time");  //integer
cJSON *json_type5 = cJSON_GetObjectItemCaseSensitive(j_request, "chat id");   //integer

    char *id_sms = create_sms(json_type1->valuestring, json_type2->valuestring, json_type3->valuestring, json_type4->valueint);  //посчитать колличество чатов //+
    //printf("%d\n", num);

        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
        cJSON_AddItemToObject(j_responce, "msg id", cJSON_CreateNumber(mx_atoi(id_sms)));

    // char *jdata = cJSON_Print(j_responce);
    // printf("%s\n", jdata);
//    
    if(id_sms == NULL)
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}
