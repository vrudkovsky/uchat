#include "server.h"

cJSON *updates_main(cJSON *j_request, cJSON *j_responce) {
    int msg_num, chat_num, id_message, id_user;
    int *new_msg_ids, *new_chat_ids;
    cJSON *new_msgs, *cJSON_message_info, *msg_id, *time, *new_chats, *json_type1;

    json_type1 = cJSON_GetObjectItemCaseSensitive(j_request, "who");
    chat_num = count_id_new_chats(json_type1->valuestring);
    msg_num = count_id_new_sms(json_type1->valuestring);

    if ((msg_num > 0) || (chat_num > 0)) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());

        if (msg_num > 0) {
            cJSON_AddItemToObject(j_responce, "new msg", cJSON_CreateNumber(msg_num));
            new_msg_ids = new_update_msgs_info(json_type1->valuestring, msg_num);
            new_msgs = cJSON_CreateArray();
            cJSON_AddItemToObject(j_responce, "new msgs", new_msgs);

            for (int i = 0, j = 0; i < msg_num; i++) {
                cJSON_AddItemToArray(new_msgs, cJSON_message_info = cJSON_CreateObject());
                cJSON_AddItemToObject(cJSON_message_info, "chat id", cJSON_CreateNumber(new_msg_ids[j++]));
                id_message = new_msg_ids[j];
                change_msg_status(new_msg_ids[j]); 
                cJSON_AddItemToObject(cJSON_message_info, "msg id", cJSON_CreateNumber(new_msg_ids[j++]));
                cJSON_AddItemToObject(cJSON_message_info, "time", cJSON_CreateNumber(new_msg_ids[j++]));
                cJSON_AddItemToObject(cJSON_message_info, "msg", cJSON_CreateString((const char *)find_message_by_id(id_message)));
            }
        }
        else
            cJSON_AddItemToObject(j_responce, "new msg", cJSON_CreateNumber(0));
        
        if (chat_num > 0) {
            cJSON_AddItemToObject(j_responce, "new chat", cJSON_CreateNumber(chat_num));
            new_chat_ids = new_update_chats_info(json_type1->valuestring, chat_num);
            new_chats = cJSON_CreateArray();
            cJSON_AddItemToObject(j_responce, "new chats", new_chats);
    
            for (int i = 0, j = 0; i < chat_num; i++) {
                cJSON_AddItemToArray(new_chats, cJSON_message_info = cJSON_CreateObject());
                change_chat_status(new_chat_ids[j]); 
                cJSON_AddItemToObject(cJSON_message_info, "chat id", cJSON_CreateNumber(new_chat_ids[j++]));
                id_user = new_chat_ids[j];
                cJSON_AddItemToObject(cJSON_message_info, "interlocutor", cJSON_CreateString((const char *)find_username_by_id(id_user)));
            }
        }
        else
            cJSON_AddItemToObject(j_responce, "new chat", cJSON_CreateNumber(0));
    }
    else 
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}
