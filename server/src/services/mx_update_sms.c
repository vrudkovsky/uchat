#include "server.h"

cJSON *mx_update_sms(cJSON *j_request, cJSON *j_responce) {
    cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "id_sms");
    cJSON *json_type2 = cJSON_GetObjectItemCaseSensitive(j_request, "text_sms");

    if (update_sms(json_type1->valueint, json_type1->valuestring)) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
    }
    else
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}
