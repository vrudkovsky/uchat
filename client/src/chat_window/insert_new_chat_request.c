#include "client.h"

void insert_new_chat_request(int chat_id, char *interlocutor) {
    chat_req_t *tmp_node;

    if (main_data.chat_req_list == NULL) {
        main_data.chat_req_list = malloc(sizeof(chat_req_t));
        tmp_node = main_data.chat_req_list;
    }

    else {
        tmp_node = main_data.chat_req_list;
        while (tmp_node->next != NULL)
            tmp_node = tmp_node->next;
    }

    tmp_node->chat_id = chat_id;
    tmp_node->interlocutor = mx_strdup(interlocutor);
    tmp_node->next = NULL;
}
