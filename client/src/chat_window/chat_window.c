#include "client.h"

void chat_window(void) {
    gtk_init(NULL, NULL);

    chat.builder = gtk_builder_new();
    chat.builder = gtk_builder_new_from_file("glade/ch_window.glade");
    chat.ch_window = GTK_WIDGET(gtk_builder_get_object(chat.builder, "ch_window"));
    chat.chats_contacts_stack = GTK_STACK(gtk_builder_get_object(chat.builder, "chats_contacts_stack"));
    chat.contacts_list = GTK_WIDGET(gtk_builder_get_object(chat.builder, "contacts_list"));
    chat.chats_list = GTK_WIDGET(gtk_builder_get_object(chat.builder, "chats_list"));

    GdkScreen * display = gdk_screen_get_default();
    GtkCssProvider *css = gtk_css_provider_new();
	gtk_css_provider_load_from_path(css, "glade/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(display, GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    g_signal_connect(chat.ch_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(chat.builder, NULL);

    gtk_widget_show(chat.ch_window);
    gtk_main();
}

// void on_event_button_release_event(GtkEntry *e) {
//     gtk_stack_set_visible_child(chats_contacts_stack, contacts_list);
// }

// void on_event2_button_release_event(GtkEntry *e) {
//     gtk_stack_set_visible_child(chats_contacts_stack, chats_list);
// }
