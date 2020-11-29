#include "server.h"

cJSON *send_msg(cJSON *j_request, cJSON *j_responce) {
    cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "who");
    cJSON *json_type2 = cJSON_GetObjectItemCaseSensitive(j_request, "whom");
    cJSON *json_type3 = cJSON_GetObjectItemCaseSensitive(j_request, "msg");
    cJSON *json_type4 = cJSON_GetObjectItemCaseSensitive(j_request, "time");
    cJSON *json_type5 = cJSON_GetObjectItemCaseSensitive(j_request, "chat id");

    int msg_id = insert_new_msg(json_type1->valuestring, json_type2->valuestring, json_type3->valuestring, json_type4->valueint, json_type5->valueint);

    if (msg_id > 0) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
        cJSON_AddItemToObject(j_responce, "msg id", cJSON_CreateNumber(msg_id));
    }
    else
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}
