#include "client.h"

static int create_new_chat_get_responce() {
    char *responce = mx_strnew(2000);
    cJSON *j_test = cJSON_CreateObject();
    cJSON *create_new_chat = cJSON_CreateObject();

    recv(main_data.sock_fd, responce, 2000, 0);

    printf("server responce->\n%s\n", responce);

    create_new_chat = cJSON_Parse(responce);
    free(responce);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(create_new_chat, "status");

    if (cJSON_IsTrue(json_type)) {
        json_type = cJSON_GetObjectItemCaseSensitive(create_new_chat, "chat id");
        return json_type->valueint;
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

    printf("client request->\n%s\n", jdata);

	cJSON_Delete(create_new_chat);
    free(jdata);
}

static int create_new_chat(char *username, char *contact_name) {
    int chat_id;

    create_new_chat_send_request(username, contact_name);
    chat_id = create_new_chat_get_responce();
    return chat_id;
}

void on_write_message_button_clicked(GtkButton *b) {
    char *username = main_data.username;
    char *contact_name = contact_info_view.user_data->username;
    contact_t *contact_node = search_contact_node(contact_name);

    if (contact_node->chat_id == -1) 
        contact_node->chat_id = create_new_chat(username, contact_name);
    // if (contact_node->chat_id > 0)
    //     open_chat_window(contact_name);
}
