#include "client.h"

static void init_contact_row_widgets(contact_row_t *node, char *username, char *initials, GtkWidget *listbox) {
    GtkStyleContext *context = NULL; 

    node->row = gtk_list_box_row_new();
    node->fixed = gtk_fixed_new();
    node->avatar_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    node->initials_label = gtk_label_new(initials);
    node->username_label = gtk_label_new(username);
    gtk_widget_set_size_request(node->avatar_box, 50, 50);
    gtk_widget_set_size_request(node->row, 230, 70);
    gtk_container_add((GtkContainer*)(node->row), node->fixed);
    gtk_fixed_put((GtkFixed*)node->fixed, node->avatar_box, 14, 8);
    gtk_fixed_put((GtkFixed*)node->fixed, node->initials_label, 25, 17);
    gtk_fixed_put((GtkFixed*)node->fixed, node->username_label, 80, 20);
    gtk_list_box_insert((GtkListBox*)(listbox), node->row, -1);
    gtk_widget_set_can_focus(node->row, FALSE);

    context = gtk_widget_get_style_context(node->row);
    gtk_style_context_add_class(context, "contact_row");
    context = gtk_widget_get_style_context(node->initials_label);
    gtk_style_context_add_class(context, "initials_lab");
    context = gtk_widget_get_style_context(node->username_label);
    gtk_style_context_add_class(context, "username_lab");
    context = gtk_widget_get_style_context(node->avatar_box);
    gtk_style_context_add_class(context, "avatar_box");

    gtk_widget_show_all(node->row);
}

void add_new_contact_row_in_list(char *username, char *initials) {
    if (chat.contact_row_list == NULL) {
        chat.contact_row_list = malloc(sizeof(contact_row_t));
        init_contact_row_widgets(chat.contact_row_list, username, initials, chat.contact_list_box);
        chat.contact_row_list->next = NULL;
    } 
    else {
        contact_row_t *new_node = malloc(sizeof(contact_row_t));
        contact_row_t *buff_node = chat.contact_row_list;
        init_contact_row_widgets(new_node, username, initials, chat.contact_list_box);
        chat.contact_row_list = new_node;
        chat.contact_row_list->next = buff_node;
    }
}

static void delete_row(contact_row_t *row_node) {
    gtk_widget_destroy(row_node->initials_label);
    gtk_widget_destroy(row_node->avatar_box);
    gtk_widget_destroy(row_node->username_label);
    gtk_widget_destroy(row_node->fixed);
    gtk_widget_destroy(row_node->row);
}

static void activate_deactivate_all_rows_in_contact_list(bool switcher) {
    contact_row_t *contact_node_row = chat.contact_row_list;
    while (contact_node_row != NULL) {
        gtk_list_box_row_set_activatable((GtkListBoxRow*)contact_node_row->row, switcher);
        gtk_list_box_row_set_selectable((GtkListBoxRow*)contact_node_row->row, switcher);
        contact_node_row = contact_node_row->next;
    }
}

static void make_contact_list_rows_inactive(void) {
    gtk_list_box_unselect_all((GtkListBox*)chat.contact_list_box);
    activate_deactivate_all_rows_in_contact_list(false);
    gtk_widget_set_opacity(chat.contact_list_box, 0.4);
    gtk_widget_set_margin_top(chat.contacts_scrolled_window, 160);
    gtk_widget_set_size_request(chat.contacts_scrolled_window, 230, 345);
}

void show_search_result(void) {
    make_contact_list_rows_inactive();
    if (search_user_data.showing_result == true)
        delete_row(search_user_data.contact_row_list);
    if (search_user_data.user_is_found) {
        search_user_data.initials = make_initials_by_username(search_user_data.username);
        init_contact_row_widgets(search_user_data.contact_row_list, search_user_data.username, search_user_data.initials, chat.contact_search_result_list_box);
        search_user_data.showing_result = true;
        gtk_list_box_select_row((GtkListBox*)chat.contact_search_result_list_box, (GtkListBoxRow*)search_user_data.contact_row_list->row);
    }
    else {
        gtk_widget_show(chat.sorry_find_user_label);
        search_user_data.showing_result = false;
    }
    gtk_stack_set_visible_child(chat.contact_search_result_stack, chat.contact_search_result_fixed);
}

static void find_user_get_responce() {
    char *responce = mx_strnew(2000);
    cJSON *j_test = cJSON_CreateObject();
    cJSON *j_responce = cJSON_CreateObject();

    // recv(main_data.sock_fd, responce, 2000, 0);
    // j_responce = cJSON_Parse(responce);
//////////////////////////////////////////////////
    if (mx_strcmp(search_user_data.username, "Janbek") == 0) {
        cJSON_AddItemToObject(j_test, "status", cJSON_CreateTrue());
    }
    else
        cJSON_AddItemToObject(j_test, "status", cJSON_CreateFalse());
    cJSON_AddItemToObject(j_test, "in contact list", cJSON_CreateFalse());
    cJSON_AddItemToObject(j_test, "email", cJSON_CreateString("vbrykov@gmail.com"));
    responce = cJSON_Print(j_test);
    printf("server responce->\n%s\n", responce);
//////////////////////////////////////////////////
    j_responce = cJSON_Parse(responce);
    free(responce);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "status");
    if (cJSON_IsTrue(json_type)) {
        search_user_data.user_is_found = true;
        json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "in contact list");
        if (cJSON_IsTrue(json_type))
            search_user_data.in_contacts = true;
        json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "email");
        search_user_data.email = mx_strdup(json_type->valuestring);
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

static void find_contact(char *username) {
    search_user_data.user_is_found = false;
    search_user_data.in_contacts = false;
    search_user_data.email = NULL;

    find_user_send_request(username);
    find_user_get_responce();
    show_search_result();
}

static void create_start_contact_list_rows(void) {
    contact_t *contact_node = main_data.contact_list;

    while (contact_node != NULL) {
        add_new_contact_row_in_list(contact_node->username, contact_node->initials);
        contact_node = contact_node->next;
    }
}

void work_with_contacts(void) {
    search_user_data.contact_row_list = malloc(sizeof(contact_row_t));
    search_user_data.showing_result = false;
    search_user_data.username = mx_strnew(30);
    chat.contact_row_list = NULL;

    if (main_data.contacts > 0)
        create_start_contact_list_rows();
    gtk_widget_show(chat.contact_search_result_label);
}

void on_find_user_field_activate(GtkEntry *e) {
    search_user_data.username = (char*)gtk_entry_get_text(e);

    gtk_stack_set_visible_child(chat.contact_search_result_stack, chat.contact_search_result_empty_fixed);
    gtk_widget_hide(chat.sorry_find_user_label);
    find_contact(search_user_data.username);
}

void on_contact_search_end_button_clicked(GtkButton *b) {
    gtk_entry_set_text((GtkEntry*)chat.contact_search_entry, "");
    gtk_stack_set_visible_child(chat.contact_search_result_stack, chat.contact_search_result_empty_fixed);
    gtk_widget_set_margin_top(chat.contacts_scrolled_window, 0);
    gtk_widget_set_size_request(chat.contacts_scrolled_window, 230, 505);
    activate_deactivate_all_rows_in_contact_list(true);
    gtk_widget_set_opacity(chat.contact_list_box, 1.0);
}
