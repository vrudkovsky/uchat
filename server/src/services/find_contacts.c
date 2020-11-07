#include "server.h"

cJSON *find_contacts(cJSON *j_request, cJSON *j_responce) {

    cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "username");

    if(mx_find_username(json_type1->valuestring) == false) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
        return j_responce;
    }
    cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
    return j_responce;
}
