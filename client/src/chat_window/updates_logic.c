#include "client.h"

static void load_new_msg(cJSON *msg_data) {
    int chat_id, msg_id, time;
    cJSON *key;

    key = cJSON_GetObjectItemCaseSensitive(msg_data, "chat id");
    chat_id = key->valueint;

    key = cJSON_GetObjectItemCaseSensitive(msg_data, "msg id");
    msg_id = key->valueint;

    key = cJSON_GetObjectItemCaseSensitive(msg_data, "time");
    time = key->valueint;

    key = cJSON_GetObjectItemCaseSensitive(msg_data, "msg");

    insert_new_message_in_chat(chat_id, msg_id, false, time, key->valuestring);
    dialog_node_update(dialog_view.user, time, false, key->valuestring);
    insert_message_widget();
}

// static void load_new_chat(cJSON *msg_data) {
//     int chat_id;
//     cJSON *key;

//     key = cJSON_GetObjectItemCaseSensitive(msg_data, "chat id");
//     chat_id = key->valueint;

//     key = cJSON_GetObjectItemCaseSensitive(msg_data, "interlocutor");

//     insert_new_chat_request(chat_id, key->valuestring);
// }

static void update_parser(cJSON *update_json) {
    int new_msg_count, new_chats_count;
    cJSON *key, *msg_data;

    key = cJSON_GetObjectItemCaseSensitive(update_json, "new msg");
    new_msg_count = key->valueint;
    for (int i = 0; i < new_msg_count; i++) {
        key = cJSON_GetObjectItemCaseSensitive(update_json, "new msgs");
        msg_data = cJSON_GetArrayItem(key, i);
        load_new_msg(msg_data);
        
        //load_new_chat()
    }

    key = cJSON_GetObjectItemCaseSensitive(update_json, "new chat");
    new_chats_count = key->valueint;
    for (int i = 0; i < new_chats_count; i++) {
        key = cJSON_GetObjectItemCaseSensitive(update_json, "new chats");
        msg_data = cJSON_GetArrayItem(key, i);
        //load_new_chat(msg_data);
    }
}

static void update_send_request(char *username) {
    cJSON *get_update = cJSON_CreateObject();
    char *jdata = NULL;

    cJSON_AddItemToObject(get_update, "action", cJSON_CreateString("update"));
    cJSON_AddItemToObject(get_update, "who", cJSON_CreateString(username));
    jdata = cJSON_Print(get_update);

    write(main_data.sock_fd, jdata, mx_strlen(jdata));

    printf("client request->\n%s\n", jdata);

	cJSON_Delete(get_update);
    free(jdata);
}

static void update_get_responce(void) {
    char *responce = mx_strnew(2000);
    cJSON *j_responce = cJSON_CreateObject();

    recv(main_data.sock_fd, responce, 2000, 0);
    printf("server responce->\n%s\n", responce);

    j_responce = cJSON_Parse(responce);
    free(responce);

    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "status");
    if (cJSON_IsTrue(json_type)) {
        update_parser(j_responce);
    }
}

void updates_logic(char *username) {
    update_send_request(username);
    update_get_responce();
}
