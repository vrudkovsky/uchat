#include "client.h"

void chat_window_init(void) {
    chat.builder = gtk_builder_new();
    chat.builder = gtk_builder_new_from_file("glade/ch_window.glade");
    chat.ch_window = GTK_WIDGET(gtk_builder_get_object(chat.builder, "ch_window"));
    chat.main_user_initials_label = GTK_WIDGET(gtk_builder_get_object(chat.builder, "main_user_initials_label"));
    chat.main_username_label = GTK_WIDGET(gtk_builder_get_object(chat.builder, "main_username_label"));
    chat.main_list = GTK_WIDGET(gtk_builder_get_object(chat.builder, "main_list"));
    chat.chats_row = GTK_WIDGET(gtk_builder_get_object(chat.builder, "chats_row"));
    chat.contacts_row = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contacts_row"));
    chat.settings_row = GTK_WIDGET(gtk_builder_get_object(chat.builder, "settings_row"));
    chat.chats_contacts_stack = GTK_STACK(gtk_builder_get_object(chat.builder, "chats_contacts_stack"));
    chat.chats_list = GTK_WIDGET(gtk_builder_get_object(chat.builder, "chats_list"));
    chat.contacts_list = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contacts_list"));
    chat.contact_search_entry = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contact_search_entry"));
    chat.contact_search_result_stack = GTK_STACK(gtk_builder_get_object(chat.builder, "contact_search_result_stack"));
    chat.contact_search_result_fixed = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contact_search_result_fixed"));
    chat.contact_search_result_empty_fixed = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contact_search_result_empty_fixed"));
    chat.contact_search_result_label = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contact_search_result_label"));
    chat.sorry_find_user_label = GTK_WIDGET(gtk_builder_get_object(chat.builder, "sorry_find_user_label"));
    chat.contact_search_result_list_box = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contact_search_result_list_box"));
    chat.contact_search_end_button = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contact_search_end_button"));
    chat.contacts_scrolled_window = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contacts_scrolled_window"));
    chat.contact_list_box = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contact_list_box"));
    chat.empty_list = GTK_WIDGET(gtk_builder_get_object(chat.builder, "empty_list"));
    chat.main_info_stack = GTK_STACK(gtk_builder_get_object(chat.builder, "main_info_stack"));
    chat.use_search_label = GTK_WIDGET(gtk_builder_get_object(chat.builder, "use_search_label"));
    chat.chat_list_box = GTK_WIDGET(gtk_builder_get_object(chat.builder, "chat_list_box"));
    chat.dont_have_chats_label = GTK_WIDGET(gtk_builder_get_object(chat.builder, "dont_have"));
    chat.chat_search_entry = GTK_WIDGET(gtk_builder_get_object(chat.builder, "chat_search_entry"));
    chat.chat_info_main = GTK_WIDGET(gtk_builder_get_object(chat.builder, "chat_info_main"));
    chat.msg_entry = GTK_WIDGET(gtk_builder_get_object(chat.builder, "msg_entry"));
    chat.send_button = GTK_WIDGET(gtk_builder_get_object(chat.builder, "send_button"));
    chat.cant_find_chats_label = GTK_WIDGET(gtk_builder_get_object(chat.builder, "find_chat_label"));
    chat.dialog_list_box = GTK_WIDGET(gtk_builder_get_object(chat.builder, "dialog_list_box"));

    contact_stack_info_init();
    gtk_label_set_text(GTK_LABEL(chat.main_username_label), main_data.username);
    gtk_label_set_text(GTK_LABEL(chat.main_user_initials_label), make_initials_by_username(main_data.username));
    gtk_stack_set_visible_child(chat.main_info_stack, chat.contact_info_empty);
    gtk_list_box_select_row((GtkListBox*)chat.main_list, (GtkListBoxRow*) chat.chats_row);
    gtk_stack_set_visible_child(chat.contact_search_result_stack, chat.contact_search_result_empty_fixed);
    gtk_widget_grab_focus(chat.contact_search_end_button);
    
    GtkStyleContext *context = gtk_widget_get_style_context((GtkWidget*)chat.chats_contacts_stack);
    gtk_style_context_add_class(context, "chats_contacts_stack");
    context = gtk_widget_get_style_context((GtkWidget*)chat.main_list);
    gtk_style_context_add_class(context, "main_list");
    context = gtk_widget_get_style_context((GtkWidget*) chat.contact_search_end_button);
    gtk_style_context_add_class(context, "contact_search_end_button");
    gtk_widget_hide(chat.cant_find_chats_label);
}

void focus_on_chats() {
    GtkListBoxRow* row = gtk_list_box_get_selected_row((GtkListBox*)chat.chat_list_box);

    gtk_stack_set_visible_child(chat.chats_contacts_stack, chat.chats_list);

    if (row == NULL) {
        gtk_stack_set_visible_child(chat.main_info_stack, chat.contact_info_empty);
    }
    else 
        gtk_stack_set_visible_child(chat.main_info_stack, chat.chat_info_main);
}

void focus_on_contacts() {
    GtkListBoxRow* row = gtk_list_box_get_selected_row((GtkListBox*)chat.contact_list_box);

    gtk_stack_set_visible_child(chat.chats_contacts_stack, chat.contacts_list);

    if (row == NULL) {
        gtk_stack_set_visible_child(chat.main_info_stack, chat.contact_info_empty);
    }
    else 
        gtk_stack_set_visible_child(chat.main_info_stack, contact_info_view.stack_page);
    
}

void focus_on_settings() {
    gtk_stack_set_visible_child(chat.chats_contacts_stack, chat.empty_list);
    gtk_stack_set_visible_child(chat.main_info_stack, chat.contact_info_empty);
}
