#include "client.h"

static void init_contact_row_widgets(contact_row_t *node, char *username) {
    node->row = gtk_list_box_row_new();
    node->fixed = gtk_fixed_new();
    node->avatar_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    node->initials_label = gtk_label_new("TD");
    node->username_label = gtk_label_new(username);
    gtk_widget_set_size_request(node->avatar_box, 50, 50);
    gtk_widget_set_size_request(node->row, 230, 70);
    gtk_container_add((GtkContainer*)(node->row), node->fixed);
    gtk_fixed_put((GtkFixed*)node->fixed, node->avatar_box, 14, 8);
    gtk_fixed_put((GtkFixed*)node->fixed, node->initials_label, 25, 17);
    gtk_fixed_put((GtkFixed*)node->fixed, node->username_label, 80, 20);
    gtk_list_box_insert((GtkListBox*)(chat.contact_list_box), node->row, -1);

    chat.context_i_label = gtk_widget_get_style_context(node->row);
    gtk_style_context_add_class(chat.context_i_label, "contact_row");
    chat.context_i_label = gtk_widget_get_style_context(node->initials_label);
    gtk_style_context_add_class(chat.context_i_label, "initials_lab");
    chat.context_i_label = gtk_widget_get_style_context(node->username_label);
    gtk_style_context_add_class(chat.context_i_label, "username_lab");
    chat.context_i_label = gtk_widget_get_style_context(node->avatar_box);
    gtk_style_context_add_class(chat.context_i_label, "avatar_box");

    gtk_widget_show(node->row);
    gtk_widget_show(node->fixed);
    gtk_widget_show(node->avatar_box);
    gtk_widget_show(node->initials_label);
    gtk_widget_show(node->username_label);
}

static void init_contact_search_row_widget(char *username) {
    tmp_data.row_search = gtk_list_box_row_new();
    tmp_data.fixed_search = gtk_fixed_new();
    tmp_data.avatar_box_search = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    tmp_data.initials_label_search = gtk_label_new("TD");
    tmp_data.username_label_search = gtk_label_new(username);
    gtk_widget_set_size_request(tmp_data.avatar_box_search, 50, 50);
    gtk_widget_set_size_request(tmp_data.row_search, 230, 70);
    gtk_container_add((GtkContainer*)(tmp_data.row_search), tmp_data.fixed_search);
    gtk_fixed_put((GtkFixed*)tmp_data.fixed_search, tmp_data.avatar_box_search, 14, 8);
    gtk_fixed_put((GtkFixed*)tmp_data.fixed_search, tmp_data.initials_label_search, 25, 17);
    gtk_fixed_put((GtkFixed*)tmp_data.fixed_search, tmp_data.username_label_search, 80, 20);
    gtk_list_box_insert((GtkListBox*)(chat.search_result_list_box), tmp_data.row_search, -1);

    tmp_data.context_label = gtk_widget_get_style_context(tmp_data.row_search);
    gtk_style_context_add_class(tmp_data.context_label, "contact_row");
    tmp_data.context_label = gtk_widget_get_style_context(tmp_data.initials_label_search);
    gtk_style_context_add_class(tmp_data.context_label, "initials_lab");
    tmp_data.context_label = gtk_widget_get_style_context(tmp_data.username_label_search);
    gtk_style_context_add_class(tmp_data.context_label, "username_lab");
    tmp_data.context_label = gtk_widget_get_style_context(tmp_data.avatar_box_search);
    gtk_style_context_add_class(tmp_data.context_label, "avatar_box");

    gtk_widget_set_margin_bottom(tmp_data.row_search, 30);
    gtk_widget_set_margin_bottom(chat.search_result_label, 10);

    gtk_widget_show(chat.search_result_label);
    gtk_widget_show(tmp_data.row_search);
    gtk_widget_show(tmp_data.fixed_search);
    gtk_widget_show(tmp_data.avatar_box_search);
    gtk_widget_show(tmp_data.initials_label_search);
    gtk_widget_show(tmp_data.username_label_search);
    
    tmp_data.showing_result = true;    
}


void add_new_contact_row_in_list(char *username) {
    if (chat.contact_row_list == NULL) {
        chat.contact_row_list = malloc(sizeof(contact_row_t));
        init_contact_row_widgets(chat.contact_row_list, username);
        chat.contact_row_list->next = NULL;
    } 
    else {
        contact_row_t *new_node = malloc(sizeof(contact_row_t));
        init_contact_row_widgets(new_node, username);
        chat.contact_row_list = new_node;
    }
}

static void find_user_send_request(char *username) {
    cJSON *j_contacts = cJSON_CreateObject();
    char *jdata = NULL;
    cJSON_AddItemToObject(j_contacts, "action", cJSON_CreateString("find user"));
    cJSON_AddItemToObject(j_contacts, "who", cJSON_CreateString(main_data.username));
    cJSON_AddItemToObject(j_contacts, "whom", cJSON_CreateString(username));
    jdata = cJSON_Print(j_contacts);
    write(main_data.sock_fd, jdata, mx_strlen(jdata));
	cJSON_Delete(j_contacts);
    free(jdata);
}

static void find_user_get_responce() {
    char *responce = mx_strnew(2000);
    cJSON *j_test = cJSON_CreateObject();
    cJSON *j_responce = cJSON_CreateObject();
    // recv(main_data.sock_fd, responce, 2000, 0);
    // j_responce = cJSON_Parse(responce);
//////////////////////////////////////////////////
    cJSON_AddItemToObject(j_test, "status", cJSON_CreateTrue());
    cJSON_AddItemToObject(j_test, "in contact list", cJSON_CreateFalse());
    cJSON_AddItemToObject(j_test, "email", cJSON_CreateString("vbrykov@gmail.com"));
    responce = cJSON_Print(j_test);
    printf("json ->\n%s\n", responce);
    j_responce = cJSON_Parse(responce);
//////////////////////////////////////////////////
    //free(responce);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "status");
    if (cJSON_IsTrue(json_type)) {
        tmp_data.user_is_found = true;
        json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "in contact list");
        if (cJSON_IsTrue(json_type))
            tmp_data.in_contacts = true;
        json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "email");
        tmp_data.find_email = mx_strdup(json_type->valuestring);
        tmp_data.find_user = mx_strdup(tmp_data.searching_user);
    }
}

static void clean_search_result(void) {
    gtk_widget_hide(chat.search_result_label);
    gtk_widget_destroy(tmp_data.initials_label_search);
    gtk_widget_destroy(tmp_data.avatar_box_search);
    gtk_widget_destroy(tmp_data.username_label_search);
    gtk_widget_destroy(tmp_data.fixed_search);
    gtk_widget_destroy(tmp_data.row_search);
}

void make_contact_list_inactive(void) {
    gtk_widget_hide(chat.contact_list_box);
    gtk_entry_set_text((GtkEntry*)chat.contact_search_entry, "");
}

void show_search_result(void) {
    make_contact_list_inactive();
    if (tmp_data.user_is_found) {
        if (tmp_data.showing_result == true)
            clean_search_result();
        init_contact_search_row_widget(tmp_data.find_user);
    }
    else {

    }
}

void find_new_contact(char *username) {
    tmp_data.in_contacts = false;
    tmp_data.user_is_found = false;
    tmp_data.find_email = NULL;

    find_user_send_request(username);
    usleep(100);
    find_user_get_responce();
    show_search_result();
}

static void create_start_contact_list_rows(void) {
    contact_t *contact_node = main_data.contact_list;
    while (contact_node != NULL) {
        add_new_contact_row_in_list(contact_node->username);
        contact_node = contact_node->next;
    }
}

void work_with_contacts(void) {
    tmp_data.showing_result = false;
    tmp_data.searching_user = mx_strnew(20);
    chat.contact_row_list = NULL;
    if (main_data.contacts > 0)
        create_start_contact_list_rows();
}

void on_find_user_field_activate(GtkEntry *e) {
    tmp_data.searching_user = (char*)gtk_entry_get_text(e);
    find_new_contact(tmp_data.searching_user);
}
