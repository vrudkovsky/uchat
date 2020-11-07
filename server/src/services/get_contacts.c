#include "server.h"



//clang -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -g -lsqlite3 main.c bussines_logic_main.c get_contacts.c mx_find_get_contacts_username.c libmx.a cJSON.a count_friends.c mx_my_username.c mx_my_mail.c

cJSON *get_contacts(cJSON *j_request, cJSON *j_responce) {

cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "who");

    int count = 0;

    if(mx_find_get_contacts_username(json_type1->valuestring) == true) { //возможно перефразировать условие
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
        count = 1;
    }

    if(count == 1) {
        int count = count_friends(json_type1->valuestring);
        char *count_1 = mx_itoa(count);
        cJSON_AddItemToObject(j_responce, "count", cJSON_CreateString(count_1)); //спросить умирослава как передавать инты
        count = 2;
        //char *my_username[] = {"one","two","three", NULL};
        char **result = mx_my_username(json_type1->valuestring);


        cJSON *j_username_arr = cJSON_CreateArray();
        int num = 0;
        while(result[num] != NULL) {
            cJSON_AddItemToObject(j_username_arr, "username", cJSON_CreateString(result[num]));
            num++;
        }
        cJSON_AddItemToObject(j_responce, "username", j_username_arr);

        num = 0;
        char **result_mail = mx_my_mail(json_type1->valuestring);
        cJSON *j_mail_arr = cJSON_CreateArray();
        while(result_mail[num] != NULL) {
            cJSON_AddItemToObject(j_mail_arr, "mail", cJSON_CreateString(result_mail[num]));
            num++;
        }
        cJSON_AddItemToObject(j_responce, "mail", j_mail_arr);


    }





    char *jdata = cJSON_Print(j_responce);
    printf("%s\n", jdata);
//    
    if(count == 0)
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}



