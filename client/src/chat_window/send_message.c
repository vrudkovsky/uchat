#include "client.h"

static chats_t *search_chat_last_node(int chat_id) {
    contact_t *tmp_contact_node = main_data.contact_list;
    chats_t *tmp_chat_node = NULL;

    while (tmp_contact_node->chat_id != chat_id)
        tmp_contact_node = tmp_contact_node->next;

    if (tmp_contact_node->chats == NULL) {
        tmp_contact_node->chats = malloc(sizeof(chats_t));
        return tmp_contact_node->chats;
    }
    else {
        tmp_chat_node = tmp_contact_node->chats;
        while (tmp_chat_node->next != NULL)
            tmp_chat_node = tmp_chat_node->next;
    }
    return tmp_chat_node;
}

void insert_new_message_in_chat(int chat_id, int msg_id, bool is_owner, int time, char *msg) {
    chats_t *chat_last_node = search_chat_last_node(chat_id);

    chat_last_node->next = NULL;
    chat_last_node->is_owner = is_owner;
    chat_last_node->msg_id = msg_id;
    chat_last_node->time = time;
    chat_last_node->msg = mx_strdup(msg);
}

static int send_message_get_responce() {
    char *responce = mx_strnew(2000);
    cJSON *j_test = cJSON_CreateObject();
    cJSON *create_new_chat = cJSON_CreateObject();

    recv(main_data.sock_fd, responce, 2000, 0);
    // printf("server responce->\n%s\n", responce);

    create_new_chat = cJSON_Parse(responce);
    free(responce);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(create_new_chat, "status");

    if (cJSON_IsTrue(json_type)) {
        json_type = cJSON_GetObjectItemCaseSensitive(create_new_chat, "msg id");
        return json_type->valueint;
    }
    return -1;
}

static void send_message_send_request(char *username, char *contact_name, int chat_id, int time, char *msg) {
    cJSON *send_message = cJSON_CreateObject();
    char *jdata = NULL;

    cJSON_AddItemToObject(send_message, "action", cJSON_CreateString("send msg"));
    cJSON_AddItemToObject(send_message, "who", cJSON_CreateString(username));
    cJSON_AddItemToObject(send_message, "whom", cJSON_CreateString(contact_name));
    cJSON_AddItemToObject(send_message, "chat id", cJSON_CreateNumber(chat_id));
    cJSON_AddItemToObject(send_message, "time", cJSON_CreateNumber(time));
    cJSON_AddItemToObject(send_message, "msg", cJSON_CreateString(msg));
    
    jdata = cJSON_Print(send_message);

    write(main_data.sock_fd, jdata, mx_strlen(jdata));
    // printf("client request->\n%s\n", jdata);

	cJSON_Delete(send_message);
    free(jdata);
}

void insert_message_widget(void) {
    message_widget_t *widget_node = dialog_view.message;

    while (widget_node != NULL)
        widget_node = widget_node->next;
    widget_node = malloc(sizeof(message_widget_t));
    widget_node->next = NULL;
    message_row_constructor(widget_node, dialog_view.user->last_msg_owner, dialog_view.user->last_msg_at, dialog_view.user->last_msg_text);
}

void dialog_node_update(dialog_t *dialog, int time, bool is_owner, char *msg) {
    // GtkStyleContext *context = NULL; 
    // context = gtk_widget_get_style_context(dialog->chat_row->update_box);
    dialog->last_msg_at = time;
    dialog->last_msg_owner = is_owner;
    dialog->last_msg_text = msg;
    // if (!is_owner) {
    //     gtk_style_context_add_class(context, "update_box_active");
    // } 
    // else 
    //     gtk_style_context_add_class(context, "update_box_inactive");
    gtk_label_set_text((GtkLabel*)dialog->chat_row->time_label, time_converter(time, 0));
    gtk_label_set_text((GtkLabel*)dialog->chat_row->msg_label, msg);
    if (!is_owner) {
        gtk_widget_hide(dialog->chat_row->you_label);
    }
    else {
        gtk_widget_show(dialog->chat_row->you_label);
    }
}

void send_message(char *msg) {
    if (mx_strlen(msg) > 0) {
        int msg_id;
        int creation_time = time(NULL);
        char *sender = main_data.username;
        char *recipient = dialog_view.user->user_info->username;
        int chat_id = dialog_view.user->user_info->chat_id;

        send_message_send_request(sender, recipient, chat_id, creation_time, msg);
        msg_id = send_message_get_responce();
        if (msg_id != -1) {
            insert_new_message_in_chat(chat_id, msg_id, true, creation_time, msg);
            dialog_node_update(dialog_view.user, creation_time, true, msg);
            insert_message_widget();
        }
    }
}

void msg_entry_activate(GtkEntry *e) {
    send_message((char*)gtk_entry_get_text((GtkEntry*)chat.msg_entry));
    gtk_entry_set_text((GtkEntry*)chat.msg_entry, "");
}

void send_button_clicked(GtkButton *b) {
    send_message((char*)gtk_entry_get_text((GtkEntry*)chat.msg_entry));
    gtk_entry_set_text((GtkEntry*)chat.msg_entry, "");
}
