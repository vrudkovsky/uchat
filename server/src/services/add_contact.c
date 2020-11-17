#include "server.h"

cJSON *add_contact(cJSON *j_request, cJSON *j_responce) {
    int count = 0;

    cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "whom");
    cJSON *json_type2 = cJSON_GetObjectItemCaseSensitive(j_request, "who");

    if(mx_add_contact(json_type2->valuestring, json_type1->valuestring) == true) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
        return j_responce;
    }

    cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}

//         Виктору функция 
//          получил ник в виде строки, если в друзьях нет - false
//           bool mx_add_contact(char *who, char *whom)    
