#include "client.h"

void chat_window_main(void) {
    gtk_init(NULL, NULL);

    chat_window_init();

    GdkScreen * display = gdk_screen_get_default();
    GtkCssProvider *css = gtk_css_provider_new();
	gtk_css_provider_load_from_path(css, "glade/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(display, GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    g_signal_connect(chat.ch_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(chat.builder, NULL);
    gtk_widget_show_all(chat.ch_window);
    gtk_main();
}

// void on_event_button_release_event(GtkEntry *e) {
//     gtk_stack_set_visible_child(chats_contacts_stack, contacts_list);
// }

// void on_event2_button_release_event(GtkEntry *e) {
//     gtk_stack_set_visible_child(chats_contacts_stack, chats_list);
// }
