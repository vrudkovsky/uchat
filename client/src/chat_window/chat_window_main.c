#include "client.h"

gboolean smth_new_loop(gpointer user_data) {

    updates_logic(main_data.username);

    if (main_data.app_status == 2)
        return true;
    return false;
}

void chat_window_main(void) {
    gtk_init(NULL, NULL);

    main_data.initials = make_initials_by_username(main_data.username);
    chat_window_init();
    start_requests();
    work_with_contacts();
    
    g_timeout_add(3000, smth_new_loop, NULL);

    GdkScreen * display = gdk_screen_get_default();
    GtkCssProvider *css = gtk_css_provider_new();
	gtk_css_provider_load_from_path(css, "glade/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(display, GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    g_signal_connect(chat.ch_window, "destroy", close_window, NULL);
    gtk_builder_connect_signals(chat.builder, NULL);
    gtk_widget_show(chat.ch_window);

    gtk_main();
}


void on_logout_button_released(GtkButton *b) {
    gtk_widget_hide(chat.ch_window);
    gtk_main_quit();
    main_data.app_status = 1;
}
