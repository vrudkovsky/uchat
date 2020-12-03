#include "client.h"

static bool get_chat_get_responce(void) {
    char *responce = mx_strnew(2000);
    cJSON *j_responce = cJSON_CreateObject();

    recv(main_data.sock_fd, responce, 2000, 0);
    // printf("server responce->\n%s\n", responce);

    j_responce = cJSON_Parse(responce);
    free(responce);

    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "status");

    if (cJSON_IsTrue(json_type)) {
        fill_chats_data(j_responce);
        return true;
    }
    else
        return false;
}

static void get_chat_send_request(char *username, int chat_id) {
    cJSON *get_chat = cJSON_CreateObject();
    char *jdata = NULL;

    cJSON_AddItemToObject(get_chat, "action", cJSON_CreateString("get chat"));
    cJSON_AddItemToObject(get_chat, "who", cJSON_CreateString(username));
    cJSON_AddItemToObject(get_chat, "chat id", cJSON_CreateNumber(chat_id));
    jdata = cJSON_Print(get_chat);

    write(main_data.sock_fd, jdata, mx_strlen(jdata));

    // printf("client request->\n%s\n", jdata);

	cJSON_Delete(get_chat);
    free(jdata);
}

static int create_new_chat_get_responce() {
    char *responce = mx_strnew(2000);
    cJSON *j_test = cJSON_CreateObject();
    cJSON *create_new_chat = cJSON_CreateObject();

    recv(main_data.sock_fd, responce, 2000, 0);

    // printf("server responce->\n%s\n", responce);

    create_new_chat = cJSON_Parse(responce);
    free(responce);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(create_new_chat, "status");

    if (cJSON_IsTrue(json_type)) {
        json_type = cJSON_GetObjectItemCaseSensitive(create_new_chat, "chat id");
        return json_type->valueint;
    }
    else {
        json_type = cJSON_GetObjectItemCaseSensitive(create_new_chat, "reason");
        if (mx_strcmp(json_type->valuestring, "chat exists") == 0) {
            json_type = cJSON_GetObjectItemCaseSensitive(create_new_chat, "chat id");
            get_chat_send_request(main_data.username, json_type->valueint);
            if (get_chat_get_responce())
                return json_type->valueint;
        }
    }
    return -1;
}

static void create_new_chat_send_request(char *username, char *contact_name) {
    cJSON *create_new_chat = cJSON_CreateObject();
    char *jdata = NULL;

    cJSON_AddItemToObject(create_new_chat, "action", cJSON_CreateString("create chat"));
    cJSON_AddItemToObject(create_new_chat, "who", cJSON_CreateString(username));
    cJSON_AddItemToObject(create_new_chat, "whom", cJSON_CreateString(contact_name));
    jdata = cJSON_Print(create_new_chat);
    write(main_data.sock_fd, jdata, mx_strlen(jdata));

    // printf("client request->\n%s\n", jdata);

	cJSON_Delete(create_new_chat);
    free(jdata);
}

static int create_new_chat(char *username, char *contact_name) {
    int chat_id;

    create_new_chat_send_request(username, contact_name);
    chat_id = create_new_chat_get_responce();

    return chat_id;
}

static void open_chat_window(contact_t *contact_node) {
    dialog_t *dialog = main_data.dialogs_list;

    gtk_stack_set_visible_child(chat.chats_contacts_stack, chat.chats_list);

    if (contact_node->chats != NULL) {
        while (dialog->user_info->chat_id != contact_node->chat_id)
            dialog = dialog->next;
        dialog_view.user = dialog;
        gtk_list_box_select_row((GtkListBox*)chat.chat_list_box, (GtkListBoxRow*)dialog->chat_row->row);
        show_dialog_info();
    }
    gtk_stack_set_visible_child(chat.main_info_stack, chat.chat_info_main);

}

void on_write_message_button_clicked(GtkButton *b) {
    char *username = main_data.username;
    char *contact_name = contact_info_view.user_data->username;
    contact_t *contact_node = search_contact_node(contact_name);

    if (contact_node->chat_id == -1) {
        return;
    }
    if (contact_node->chat_id > 0)
        open_chat_window(contact_node);
}
