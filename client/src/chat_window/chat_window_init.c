#include "client.h"

void chat_window_init(void) {
    chat.builder = gtk_builder_new();
    chat.builder = gtk_builder_new_from_file("glade/ch_window.glade");
    chat.ch_window = GTK_WIDGET(gtk_builder_get_object(chat.builder, "ch_window"));
    chat.main_list = GTK_WIDGET(gtk_builder_get_object(chat.builder, "main_list"));
    chat.chats_row = GTK_WIDGET(gtk_builder_get_object(chat.builder, "chats_row"));
    chat.contacts_row = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contacts_row"));
    chat.chats_contacts_stack = GTK_STACK(gtk_builder_get_object(chat.builder, "chats_contacts_stack"));
    chat.chats_list = GTK_WIDGET(gtk_builder_get_object(chat.builder, "chats_list"));
    chat.contacts_list = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contacts_list"));

    gtk_list_box_select_row ((GtkListBox*)chat.main_list, (GtkListBoxRow*)chat.contacts_row);
}

void focus_on_chats() {
    gtk_stack_set_visible_child(chat.chats_contacts_stack, chat.chats_list);
}

void focus_on_contacts() {
    gtk_stack_set_visible_child(chat.chats_contacts_stack, chat.contacts_list);
}
