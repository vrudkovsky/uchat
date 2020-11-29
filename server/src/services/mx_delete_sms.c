#include "server.h"

cJSON *mx_delete_sms(cJSON *j_request, cJSON *j_responce) {
    cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "id_sms");

    if (delete_sms(json_type1->valueint)) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
    }
    else
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}
