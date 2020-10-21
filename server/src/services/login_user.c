#include "server.h"

cJSON *login_user(cJSON *j_request, cJSON *j_responce) {
    
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_request, "username");
    if(mx_find_username(json_type->valuestring) != 0) {
        json_type = cJSON_GetObjectItemCaseSensitive(j_request, "password");
             if(mx_find_password(json_type->valuestring) != 0) {
                 cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
                 //return j_responce;
            }
            else {
                cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
               // return j_responce;
            } 
    }
    return j_responce;
}
