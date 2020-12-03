#include "client.h"

chats_t *search_last_msg_node(chats_t *chat_info) {
    chats_t *lats_msg_node = chat_info;

    while (lats_msg_node->next != NULL)
        lats_msg_node = lats_msg_node->next;
    return lats_msg_node;
}

static void create_chat_row(dialog_t *dialog, contact_t *user_info, chats_t *chat_info, chat_row_t *row) {
    chats_t *lats_msg_node = NULL;
    GtkStyleContext *context = NULL; 

    lats_msg_node = search_last_msg_node(chat_info);
    dialog->last_msg_text = lats_msg_node->msg;
    dialog->last_msg_at = lats_msg_node->time;
    if (lats_msg_node->is_owner)
        dialog->last_msg_owner = true;
    dialog->updates = false;
    
    row->row = gtk_list_box_row_new();
    row->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    row->top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    row->fixed = gtk_fixed_new();
    row->update_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    row->time_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    row->msg_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    row->username_label = gtk_label_new(user_info->username);
    row->time_label = gtk_label_new(time_converter(lats_msg_node->time, 0));
    row->you_label = gtk_label_new("You: ");
    row->msg_label = gtk_label_new(lats_msg_node->msg);

    gtk_widget_set_size_request(row->row, 230, 70);
    gtk_widget_set_size_request(row->time_box, 110, -1);

    gtk_box_pack_start((GtkBox*)row->main_box, row->top_box, false, false, 10);
    gtk_box_pack_start((GtkBox*)row->top_box, row->fixed, false, false, 0);
    gtk_fixed_put((GtkFixed*)row->fixed, row->update_box, 10, 0);
    gtk_fixed_put((GtkFixed*)row->fixed, row->time_box, 110, 0);

    gtk_box_pack_start((GtkBox*)row->time_box, row->time_label, false, false, 0);
    gtk_box_pack_start((GtkBox*)row->main_box, row->msg_box, false, false, 0);
    gtk_box_pack_start((GtkBox*)row->msg_box, row->you_label, false, false, 0);
    gtk_box_pack_start((GtkBox*)row->msg_box, row->msg_label, false, false, 0);

    gtk_widget_set_margin_start(row->username_label, 3);
    gtk_widget_set_margin_end(row->username_label, 3);
    gtk_widget_set_margin_top(row->username_label, 0);
    gtk_widget_set_margin_bottom(row->username_label, 1);
    gtk_widget_set_margin_start(row->msg_box, 13);
    gtk_widget_set_margin_top(row->msg_box, 3);
    gtk_widget_set_halign(row->time_label, GTK_ALIGN_END);
    gtk_widget_set_margin_top(row->time_label, 0);
    gtk_label_set_max_width_chars((GtkLabel*)row->msg_label, 26);
    gtk_label_set_ellipsize((GtkLabel*)row->msg_label, PANGO_ELLIPSIZE_END);

    gtk_container_add((GtkContainer*)(row->update_box), row->username_label);
    gtk_container_add((GtkContainer*)(row->row), row->main_box);
    gtk_list_box_insert((GtkListBox*)(chat.chat_list_box), row->row, 0);
    gtk_widget_set_can_focus(row->row, FALSE);

    context = gtk_widget_get_style_context(row->row);
    gtk_style_context_add_class(context, "chat_row");
    context = gtk_widget_get_style_context(row->msg_label);
    gtk_style_context_add_class(context, "msg_label");
    context = gtk_widget_get_style_context(row->time_label);
    gtk_style_context_add_class(context, "time_lab");
    context = gtk_widget_get_style_context(row->username_label);
    gtk_style_context_add_class(context, "username_chat_lab");
    context = gtk_widget_get_style_context(row->update_box);
    gtk_style_context_add_class(context, "update_box");

    gtk_widget_show_all(row->row);
    if (!dialog->last_msg_owner)
        gtk_widget_hide(row->you_label);
}

static void fill_node_with_data(dialog_t *dialog) {
    contact_t *user_info = NULL;
    chats_t *chat_info = NULL;
    chat_row_t *row = NULL;

    dialog->last_msg_at = 0;
    dialog->last_msg_owner = false;
    dialog->last_msg_text = NULL;
    dialog->updates = false;
    user_info = dialog->user_info;
    chat_info = user_info->chats;
    dialog->chat_row = malloc(sizeof(chat_row_t));
    row = dialog->chat_row;
    
    create_chat_row(dialog, user_info, chat_info, row);
}

void add_dialog_node_FIFO(contact_t *contact_data) {
    dialog_t *dialog_node = NULL;

    if (main_data.dialogs_list == NULL) {
        main_data.dialogs_list = malloc(sizeof(dialog_t));
        dialog_node = main_data.dialogs_list;
        dialog_node->next = NULL;
    }
    else {
       dialog_node = malloc(sizeof(dialog_t));
       dialog_node->next = main_data.dialogs_list;
       main_data.dialogs_list = dialog_node;
    }
    dialog_node->user_info = contact_data;
    fill_node_with_data(dialog_node);
}
