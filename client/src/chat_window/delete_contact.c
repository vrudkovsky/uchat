#include "client.h"

static void free_contact_info_memory(contact_t *node) {
    contact_info_view.user_data = malloc(sizeof(contact_t));
    contact_info_view.user_data->username = mx_strdup(node->username);
    contact_info_view.user_data->email = mx_strdup(node->email);
    contact_info_view.user_data->initials = mx_strdup(node->initials);

    free(node->username);
    free(node->initials);
    free(node->email);
    //delete_chats();  TO_DO
    free(node);
}

static void destroy_contact_row(contact_row_t *node) {
    gtk_widget_destroy(node->row);
    free(node);
}


static void delete_user_info_from_contacts(short position) {
    contact_t *node = main_data.contact_list;
    contact_t *prev = NULL;
    
    if (position == 0) {
        main_data.contact_list = node->next;
        free_contact_info_memory(node);
    }
    else {
        for (short i = 0; i < position; i++) {
            prev = node;
            node = node->next;
        }
        prev->next = node->next;
        free_contact_info_memory(node);
    }
}

static void delete_contact_row_from_list(short position) {
    contact_row_t *node = chat.contact_row_list;
    contact_row_t *prev = NULL;
    
    if (position == 0) {
        chat.contact_row_list = node->next;
        destroy_contact_row(node);
    }
    else {
        for (short i = 0; i < position; i++) {
            prev = node;
            node = node->next;
        }
        prev->next = node->next;
        destroy_contact_row(node);
    }
}

static bool delete_contact_get_responce() {
    char *responce = mx_strnew(2000);
    cJSON *j_test = cJSON_CreateObject();
    cJSON *delete_contact_responce = cJSON_CreateObject();

    recv(main_data.sock_fd, responce, 2000, 0);
    // printf("server responce->\n%s\n", responce);

    delete_contact_responce = cJSON_Parse(responce);
    free(responce);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(delete_contact_responce, "status");
    if (cJSON_IsTrue(json_type))
        return true;
    // printf("%s\n", "can not delete this contact");
    return false;
}

static void delete_contact_send_request(char *username) {
    cJSON *delete_contact = cJSON_CreateObject();
    char *jdata = NULL;

    cJSON_AddItemToObject(delete_contact, "action", cJSON_CreateString("delete contact"));
    cJSON_AddItemToObject(delete_contact, "who", cJSON_CreateString(main_data.username));
    cJSON_AddItemToObject(delete_contact, "whom", cJSON_CreateString(username));
    jdata = cJSON_Print(delete_contact);

    // printf("client request->\n%s\n", jdata);
    write(main_data.sock_fd, jdata, mx_strlen(jdata));

	cJSON_Delete(delete_contact);
    free(jdata);
}

void on_delete_contact_button_clicked(GtkButton *b) {
    short num;

    delete_contact_send_request(contact_info_view.user_data->username);
    if (delete_contact_get_responce()) {
        if (contact_info_view.search_view_is_active) {
            num = search_user_in_local_contact_list(contact_info_view.user_data->username);
        }
        else {
            num = gtk_list_box_row_get_index(gtk_list_box_get_selected_row((GtkListBox*)chat.contact_list_box));
        }
        delete_user_info_from_contacts(num);
        main_data.contacts--;
        delete_contact_row_from_list(num);
        gtk_widget_hide(contact_info_view.delete_contact_button);
        gtk_widget_show(contact_info_view.add_contact_button);
        gtk_widget_set_sensitive(contact_info_view.write_message_button, FALSE);
    }
    if (main_data.contacts == 0)
        gtk_widget_show(chat.use_search_label);
}
