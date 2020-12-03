#include "client.h"

void contact_stack_info_init(void) {
    chat.contact_info_empty = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contact_info_empty"));

    contact_info_view.stack_page = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contact_info_view"));
    contact_info_view.initials_label = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contact_info_initials_label"));
    contact_info_view.username_label = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contact_info_username_label"));
    contact_info_view.email_label = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contact_info_email_label"));
    contact_info_view.write_message_button = GTK_WIDGET(gtk_builder_get_object(chat.builder, "write_message_button"));
    contact_info_view.add_contact_button = GTK_WIDGET(gtk_builder_get_object(chat.builder, "add_contact_button"));
    contact_info_view.delete_contact_button = GTK_WIDGET(gtk_builder_get_object(chat.builder, "delete_contact_button"));
}
