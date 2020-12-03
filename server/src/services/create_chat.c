#include "server.h"

cJSON *create_new_chat(cJSON *j_request, cJSON *j_responce) {
    int chat_id;
    int exist_chat_id;

    cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "who");
    cJSON *json_type2 = cJSON_GetObjectItemCaseSensitive(j_request, "whom");

    exist_chat_id = mx_find_chat_with_contact(json_type1->valuestring, json_type2->valuestring);

    if (exist_chat_id == -1) {
        chat_id = mx_create_new_chat(json_type1->valuestring, json_type2->valuestring);
        if (chat_id > 0) {
            cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
            cJSON_AddItemToObject(j_responce, "chat id", cJSON_CreateNumber(chat_id));
        }
        else {
            cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
            cJSON_AddItemToObject(j_responce, "reason", cJSON_CreateString("unknown"));
        }
    }  
    else {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
        cJSON_AddItemToObject(j_responce, "reason", cJSON_CreateString("chat exists"));
        cJSON_AddItemToObject(j_responce, "chat id", cJSON_CreateNumber(exist_chat_id));
    }
    return j_responce;
}
