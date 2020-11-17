#include "client.h"

void add_new_chat_in_list(cJSON *chat) {
    cJSON *json = cJSON_GetObjectItemCaseSensitive(chat, "user 1");
    cJSON *json1 = cJSON_GetObjectItemCaseSensitive(chat, "user 2");
    printf("%s - %s\n", json->valuestring, json1->valuestring);
}

void fill_chats_data(cJSON *responce) {
    int chats_count;
    cJSON *chat; 

    cJSON *json = cJSON_GetObjectItemCaseSensitive(responce, "chats count");
    chats_count = json->valueint;
    json = cJSON_GetObjectItemCaseSensitive(responce, "chats");

    for (int i = 0; i < chats_count; i++) {
        chat = cJSON_GetArrayItem(json, i);
        add_new_chat_in_list(chat);
    }
}
