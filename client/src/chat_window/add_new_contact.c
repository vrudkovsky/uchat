#include "client.h" 

static void add_new_contact_get_responce() {
    char *responce = mx_strnew(2000);
    cJSON *j_test = cJSON_CreateObject();
    cJSON *add_contact_responce = cJSON_CreateObject();

    // recv(main_data.sock_fd, responce, 2000, 0);
    // j_responce = cJSON_Parse(responce);
//////////////////////////////////////////////////
    cJSON_AddItemToObject(j_test, "status", cJSON_CreateTrue());
    responce = cJSON_Print(j_test);
    printf("server responce->\n%s\n", responce);
//////////////////////////////////////////////////
    add_contact_responce = cJSON_Parse(responce);
    free(responce);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(add_contact_responce, "status");
    if (cJSON_IsTrue(json_type)) {
        add_new_contact_data_in_list(contact_info_view.user_data->username, contact_info_view.user_data->email);

        contact_row_t *first_node = malloc(sizeof(contact_row_t));
        first_node->next = chat.contact_row_list;
        chat.contact_row_list = first_node;
        init_contact_row_widgets(chat.contact_row_list, contact_info_view.user_data->username, contact_info_view.user_data->initials, chat.contact_list_box, 0);

        gtk_widget_set_sensitive(contact_info_view.write_message_button, TRUE);
        gtk_widget_hide(contact_info_view.add_contact_button);
        gtk_widget_show(contact_info_view.delete_contact_button);
        if (contact_info_view.search_view_is_active)
            activate_deactivate_all_rows_in_contact_list(false);
        main_data.contacts++;
    }
    else 
        printf("%s\n", "can not add this contact");
}

static void add_new_contact_send_request(char *username) {
    cJSON *add_contact = cJSON_CreateObject();
    char *jdata = NULL;

    cJSON_AddItemToObject(add_contact, "action", cJSON_CreateString("add contact"));
    cJSON_AddItemToObject(add_contact, "who", cJSON_CreateString(main_data.username));
    cJSON_AddItemToObject(add_contact, "whom", cJSON_CreateString(username));
    jdata = cJSON_Print(add_contact);
    write(main_data.sock_fd, jdata, mx_strlen(jdata));
	cJSON_Delete(add_contact);
    free(jdata);
}

void on_add_contact_button_clicked(GtkButton *b) {
    add_new_contact_send_request(contact_info_view.user_data->username);
    add_new_contact_get_responce();
}
