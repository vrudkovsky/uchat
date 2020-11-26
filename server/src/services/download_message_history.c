#include "server.h"

cJSON *download_message_history(cJSON *j_request, cJSON *j_responce) {
    cJSON *json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "who");
    cJSON *cJSON_chats, *cJSON_info_chat, *cJSON_msg_id, *cJSON_time, *cJSON_is_owner, *cJSON_msgs;
    int num = mx_count_chats(json_type1->valuestring);
    int msg_count;
    int *chats_id;
    int *msg_id;
    int *msg_time;
    int *is_owner;
    char **msg_text;

    if (num > 0) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
        cJSON_AddItemToObject(j_responce, "chats count", cJSON_CreateNumber(num));

        chats_id = mx_id_chatss(json_type1->valuestring, num);
    
        cJSON_chats = cJSON_CreateArray();
        cJSON_AddItemToObject(j_responce, "chats", cJSON_chats);

        for (int i = 0; i < num; i++) {
            cJSON_AddItemToArray(cJSON_chats, cJSON_info_chat = cJSON_CreateObject());
            cJSON_AddItemToObject(cJSON_info_chat, "chat id", cJSON_CreateNumber(chats_id[i]));

            msg_count = mx_count_sms(chats_id[i]);
            cJSON_AddItemToObject(cJSON_info_chat, "msg count", cJSON_CreateNumber(msg_count));

            cJSON_AddItemToObject(cJSON_info_chat, "interlocutor", cJSON_CreateString(mx_search_interlocutor(chats_id[i], json_type1->valuestring)));

            cJSON_msg_id = cJSON_CreateArray();
            cJSON_AddItemToObject(cJSON_info_chat, "msg id", cJSON_msg_id);
    
            msg_id = get_msgs_ids(chats_id[i], msg_count);
            for (int j = 0; j < msg_count; j++)
                cJSON_AddItemToArray(cJSON_msg_id, cJSON_CreateNumber(msg_id[j]));

			cJSON_time = cJSON_CreateArray();
            cJSON_AddItemToObject(cJSON_info_chat, "time", cJSON_time);

            msg_time = mx_get_time(chats_id[i], msg_count);
            for (int j = 0; j < msg_count; j++)
                cJSON_AddItemToArray(cJSON_time, cJSON_CreateNumber(msg_time[j]));

            cJSON_is_owner = cJSON_CreateArray();
            cJSON_AddItemToObject(cJSON_info_chat, "is_owner", cJSON_is_owner);
            
            is_owner = mx_is_msg_owner(json_type1->valuestring, msg_count, chats_id[i]);
            for (int j = 0; j < msg_count; j++)
                cJSON_AddItemToArray(cJSON_is_owner, cJSON_CreateNumber(is_owner[j]));

            cJSON_msgs = cJSON_CreateArray();
            cJSON_AddItemToObject(cJSON_info_chat, "msg", cJSON_msgs);

            msg_text = mx_get_msg_text(chats_id[i], msg_count);
            for (int j = 0; j < msg_count; j++)
                cJSON_AddItemToArray(cJSON_msgs, cJSON_CreateString(msg_text[j]));
        }
    }
    else 
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}
