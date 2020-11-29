#include "server.h"
#include "cJSON.h"

cJSON *get_chat(cJSON *j_request, cJSON *j_responce) {
    cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "who");
    cJSON *json_type2 = cJSON_GetObjectItemCaseSensitive(j_request, "chat id");
    cJSON *cJSON_chats, *cJSON_info_chat, *cJSON_msg_id, *cJSON_time, *cJSON_is_owner, *cJSON_msgs;

    int chat_id = json_type2->valueint;
    int msg_count;
    int *msg_id;
    int *msg_time;
    int *is_owner;
    char **msg_text;
    
    if (check_chat_by_id(chat_id)) {

        change_chat_status(chat_id);
    
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
        cJSON_AddItemToObject(j_responce, "chats count", cJSON_CreateNumber(1));

        cJSON_chats = cJSON_CreateArray();
        cJSON_AddItemToObject(j_responce, "chats", cJSON_chats);

        cJSON_AddItemToArray(cJSON_chats, cJSON_info_chat = cJSON_CreateObject());
        cJSON_AddItemToObject(cJSON_info_chat, "chat id", cJSON_CreateNumber(chat_id));
    
        msg_count = mx_count_sms(chat_id);
        cJSON_AddItemToObject(cJSON_info_chat, "msg count", cJSON_CreateNumber(msg_count));
        cJSON_AddItemToObject(cJSON_info_chat, "interlocutor", cJSON_CreateString(mx_search_interlocutor(chat_id, json_type1->valuestring)));

        cJSON_msg_id = cJSON_CreateArray();
        cJSON_AddItemToObject(cJSON_info_chat, "msg id", cJSON_msg_id);
    
        msg_id = get_msgs_ids(chat_id, msg_count);
        for (int j = 0; j < msg_count; j++) {
            cJSON_AddItemToArray(cJSON_msg_id, cJSON_CreateNumber(msg_id[j]));
            change_msg_status(msg_id[j]);
        }

		cJSON_time = cJSON_CreateArray();
        cJSON_AddItemToObject(cJSON_info_chat, "time", cJSON_time);

        msg_time = mx_get_time(chat_id, msg_count);
        for (int j = 0; j < msg_count; j++)
            cJSON_AddItemToArray(cJSON_time, cJSON_CreateNumber(msg_time[j]));

        cJSON_is_owner = cJSON_CreateArray();
        cJSON_AddItemToObject(cJSON_info_chat, "is_owner", cJSON_is_owner);
            
        is_owner = mx_is_msg_owner(json_type1->valuestring, msg_count, chat_id);
        for (int j = 0; j < msg_count; j++)
            cJSON_AddItemToArray(cJSON_is_owner, cJSON_CreateNumber(is_owner[j]));

        cJSON_msgs = cJSON_CreateArray();
        cJSON_AddItemToObject(cJSON_info_chat, "msg", cJSON_msgs);

        msg_text = mx_get_msg_text(chat_id, msg_count);
        for (int j = 0; j < msg_count; j++)
            cJSON_AddItemToArray(cJSON_msgs, cJSON_CreateString(msg_text[j]));
    }
    else {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    }
    return j_responce;
}
