#include "client.h"

static void fill_chat_list(chats_t *chat_node, cJSON *chat, int i) {
    cJSON *array_element;
    cJSON *key;

    key = cJSON_GetObjectItemCaseSensitive(chat, "is owner");
    array_element = cJSON_GetArrayItem(key, i);

    if (array_element->valueint == 1) {
        chat_node->is_owner = true;
    }
    else
        chat_node->is_owner = false;

    key = cJSON_GetObjectItemCaseSensitive(chat, "msg id");
    array_element = cJSON_GetArrayItem(key, i);
    chat_node->msg_id = array_element->valueint;

    key = cJSON_GetObjectItemCaseSensitive(chat, "time");
    array_element = cJSON_GetArrayItem(key, i);
    chat_node->time = array_element->valueint;

    key = cJSON_GetObjectItemCaseSensitive(chat, "msg");
    array_element = cJSON_GetArrayItem(key, i);
    chat_node->msg = mx_strdup(array_element->valuestring);
}

contact_t *search_contact_node(char *contact_name) {
    contact_t *contact_node = main_data.contact_list;
    while (mx_strcmp(contact_name, contact_node->username) != 0)
        contact_node = contact_node->next;
    return contact_node;
}

void add_new_chats_in_chats_list(cJSON *chat) {
    char *contact_name;
    contact_t *contact_node = NULL;

    cJSON *first = cJSON_GetObjectItemCaseSensitive(chat, "interlocutor");
    contact_name = mx_strdup(first->valuestring); 
    contact_node = search_contact_node(contact_name);

    first = cJSON_GetObjectItemCaseSensitive(chat, "chat id");
    contact_node->chat_id = first->valueint;

    first = cJSON_GetObjectItemCaseSensitive(chat, "msg count");

    chats_t *last_node = NULL;
    chats_t *tmp_node;
//FIFO STORAGE FOR MESSAGES 
    for (int i = 0; i < first->valueint; i++) {
        last_node = malloc(sizeof(chats_t));
        fill_chat_list(last_node, chat, i);
        last_node->next = NULL;

        if (contact_node->chats == NULL) {
            contact_node->chats = last_node;
        }
        else {
            tmp_node = contact_node->chats;
            while (tmp_node->next) 
                tmp_node = tmp_node->next;
            tmp_node->next = last_node;
        }
    }
//FILO STORAGE FOR MESSAGES 
    // chats_t *first_node = NULL;
    // for (int i = 0; i < first->valueint; i++) {
    //     first_node = malloc(sizeof(chats_t));
    //     fill_chat_list(first_node, chat, i);

    //     if (contact_node->chats == NULL) {
    //         first_node->next = NULL;
    //         contact_node->chats = first_node;
    //     }
    //     else {
    //         first_node->next = contact_node->chats;
    //         contact_node->chats = first_node;
    //     }
    // }
}

void fill_chats_data(cJSON *responce) {
    cJSON *chat;
    cJSON *json = cJSON_GetObjectItemCaseSensitive(responce, "chats count");
    int chats_count = json->valueint;

    json = cJSON_GetObjectItemCaseSensitive(responce, "chats");

    for (int i = 0; i < chats_count; i++) {
        chat = cJSON_GetArrayItem(json, i);
        add_new_chats_in_chats_list(chat);
    }
}
