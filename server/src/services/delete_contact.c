#include "server.h"

cJSON *delete_contact(cJSON *j_request, cJSON *j_responce) {
    cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "whom");
    cJSON *json_type2 = cJSON_GetObjectItemCaseSensitive(j_request, "who");

    if (mx_delete_contact(json_type2->valuestring, json_type1->valuestring)) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
    }
    else
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}
