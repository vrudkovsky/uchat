#include "server.h"
#include "cJSON.h"

cJSON *find_user(cJSON *j_request, cJSON *j_responce) {

    cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "whom");
    cJSON *json_type2 = cJSON_GetObjectItemCaseSensitive(j_request, "who");

    if (mx_find_username(json_type1->valuestring) == true) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());

        if (in_contact_list(json_type2->valuestring, json_type1->valuestring) == false) {
            cJSON_AddItemToObject(j_responce, "in contact list", cJSON_CreateFalse());
        } 
        else
            cJSON_AddItemToObject(j_responce, "in contact list", cJSON_CreateTrue());

        const char *mail = in_search_mail(json_type1->valuestring); 
        cJSON_AddItemToObject(j_responce, "email", cJSON_CreateString(mail));
    }
    else
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}

//         Виктору функция 
//          получил ник в виде строки, если в друзьях нет - false
//           bool in_contact_list(char *username)    
