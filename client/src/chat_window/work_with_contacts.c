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

static void create_start_contact_list_rows(void) {
    contact_t *contact_node = main_data.contact_list;
    while (contact_node != NULL) {
        add_new_contact_row_in_list(contact_node->username);
        contact_node = contact_node->next;
    }
}

void work_with_contacts(void) {
    chat.contact_row_list = NULL;
    if (main_data.contacts > 0)
        create_start_contact_list_rows();
}
