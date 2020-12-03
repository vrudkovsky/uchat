#include "client.h"

void message_row_constructor(message_widget_t *message_gui, bool is_owner, int time, char *msg) {
    GtkStyleContext *context = NULL;
    GtkAdjustment *adjust;

    message_gui->row = gtk_list_box_row_new();

    message_gui->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    message_gui->avatar_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    message_gui->work_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    message_gui->message_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    message_gui->control_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    
    if (!is_owner) {
        message_gui->initials_label = gtk_label_new(dialog_view.user->user_info->initials);
    }
    else
        message_gui->initials_label = gtk_label_new(main_data.initials);
    message_gui->msg_label = gtk_label_new(msg);
    gtk_label_set_line_wrap((GtkLabel*)message_gui->msg_label, TRUE);
    gtk_label_set_max_width_chars((GtkLabel*)message_gui->msg_label, 60);

    message_gui->time_label = gtk_label_new(time_converter(time, 1));

    
    gtk_widget_set_size_request(message_gui->avatar_box, 30, 30);
    gtk_widget_set_size_request(message_gui->initials_label, 30, 30);
    gtk_container_add((GtkContainer*)(message_gui->avatar_box), message_gui->initials_label);

    if (dialog_view.user_num != is_owner)
        gtk_box_pack_start((GtkBox*)message_gui->main_box, message_gui->avatar_box, false, false, 5);
    dialog_view.user_num = is_owner;
    
    gtk_box_pack_start((GtkBox*)message_gui->main_box, message_gui->work_box, false, false, 0);
    gtk_box_pack_start((GtkBox*)message_gui->work_box, message_gui->message_box, false, false, 0);
    if (!is_owner)
        gtk_box_pack_start((GtkBox*)message_gui->work_box, message_gui->control_box, false, false, 0);
    gtk_box_pack_start((GtkBox*)message_gui->message_box, message_gui->msg_label, false, false, 10);
    gtk_box_pack_start((GtkBox*)message_gui->message_box, message_gui->time_label, false, false, 0);

    gtk_container_add((GtkContainer*)(message_gui->row), message_gui->main_box);

    gtk_widget_set_margin_end(message_gui->row, 13);
    gtk_widget_set_margin_start(message_gui->row, 13);
    gtk_widget_set_margin_top(message_gui->row, 8);
    gtk_widget_set_margin_end(message_gui->main_box, 3);
    gtk_widget_set_margin_start(message_gui->main_box, 3);
    gtk_widget_set_margin_end(message_gui->msg_label, 10);
    gtk_widget_set_margin_start(message_gui->msg_label, 10);
    gtk_widget_set_margin_end(message_gui->time_label, 10);
    gtk_widget_set_margin_start(message_gui->time_label, 10);
    gtk_widget_set_margin_bottom(message_gui->time_label, 7);

    if (is_owner) {
        gtk_widget_set_halign(message_gui->avatar_box, GTK_ALIGN_START);
        gtk_widget_set_halign(message_gui->time_label, GTK_ALIGN_START);
        gtk_widget_set_halign(message_gui->msg_label, GTK_ALIGN_START);
        gtk_widget_set_halign(message_gui->row, GTK_ALIGN_START);
        context = gtk_widget_get_style_context(message_gui->message_box);
        gtk_style_context_add_class(context, "message_box_owner");
        context = gtk_widget_get_style_context(message_gui->row);
        gtk_style_context_add_class(context, "message_row_owner");
    }
    else {
        gtk_widget_set_halign(message_gui->avatar_box, GTK_ALIGN_END);
        gtk_widget_set_halign(message_gui->time_label, GTK_ALIGN_END);
        gtk_widget_set_halign(message_gui->msg_label, GTK_ALIGN_END);
        gtk_widget_set_halign(message_gui->row, GTK_ALIGN_END);
        context = gtk_widget_get_style_context(message_gui->message_box);
        gtk_style_context_add_class(context, "message_box");
        context = gtk_widget_get_style_context(message_gui->row);
        gtk_style_context_add_class(context, "message_row");      
    }

    gtk_list_box_insert((GtkListBox*)(chat.dialog_list_box), message_gui->row, -1);

    gtk_widget_set_can_focus(message_gui->row, FALSE);

    context = gtk_widget_get_style_context(message_gui->msg_label);
    gtk_style_context_add_class(context, "message_label");
    context = gtk_widget_get_style_context( message_gui->time_label);
    gtk_style_context_add_class(context, "time_label");
    context = gtk_widget_get_style_context(message_gui->initials_label);
    gtk_style_context_add_class(context, "initials_label");
    context = gtk_widget_get_style_context(message_gui->avatar_box);
    gtk_style_context_add_class(context, "message_avatar_box");

    gtk_widget_show_all(message_gui->row);
    adjust = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(chat.dialog_scrolled_window));
    gtk_adjustment_set_value(adjust, 100000);
}

static void show_message_widgets(void) {
    chats_t *chat = dialog_view.user->user_info->chats;
    message_widget_t *first_node = NULL;
    message_widget_t *tmp_node = NULL;

    while (chat != NULL) {
        first_node = malloc(sizeof(message_widget_t));
        first_node->next = NULL;
        message_row_constructor(first_node, chat->is_owner, chat->time, chat->msg);
        if (dialog_view.message == NULL) {
            dialog_view.message = first_node;
        }
        else {
            tmp_node = dialog_view.message;
            while (tmp_node->next != NULL)
                tmp_node = tmp_node->next;
            tmp_node->next = first_node;
        }
        chat = chat->next;
    }
}

static void clean_message_widgets(void) {
    message_widget_t *tmp_node;
    int i = 1;

    while (dialog_view.message) {
        tmp_node = dialog_view.message;
        dialog_view.message = dialog_view.message->next;

        gtk_widget_destroy(tmp_node->initials_label);
        gtk_widget_destroy(tmp_node->avatar_box);
        gtk_widget_destroy(tmp_node->time_label);
        gtk_widget_destroy(tmp_node->msg_label);
        gtk_widget_destroy(tmp_node->control_box);
        gtk_widget_destroy(tmp_node->message_box);
        gtk_widget_destroy(tmp_node->work_box);
        gtk_widget_destroy(tmp_node->main_box);
        gtk_widget_destroy(tmp_node->row);

        free(tmp_node);
    }
    dialog_view.message = NULL;
}

static void show_dialog_info(void) {
    if (dialog_view.message != NULL)
        clean_message_widgets();
    if (dialog_view.message == NULL)
        show_message_widgets();
}

void chat_list_row_activated(void) {
    short num = gtk_list_box_row_get_index(gtk_list_box_get_selected_row((GtkListBox*)chat.chat_list_box));

    dialog_view.user = main_data.dialogs_list;
    dialog_view.user_num = 2;

    for (int i = 0; i < num; i++)
       dialog_view.user = dialog_view.user->next;
    show_dialog_info();
    gtk_stack_set_visible_child(chat.main_info_stack, chat.chat_info_main);
}
