#include "server.h"

cJSON *login_user(cJSON *j_request, cJSON *j_responce) {

    cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "username");

    if(mx_find_username(json_type1->valuestring) == false) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
        return j_responce;
    }
    cJSON *json_type2 = cJSON_GetObjectItemCaseSensitive(j_request, "password");
    if(mx_find_password(json_type2->valuestring, json_type1->valuestring) == false) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
        return j_responce;
    }
    cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
    //free(json_type1);
    //free(json_type2);
    return j_responce;
}
