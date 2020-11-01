#include "client.h"

void close_window(void) {
    main_data.app_status = 3;
    gtk_main_quit();
}

void log_reg_window(void) {
    gtk_init(NULL, NULL);

    log_reg_widgets();
    log_reg_actions();
    // GdkScreen * display = gdk_screen_get_default();
    // GtkCssProvider *css = gtk_css_provider_new();
	// gtk_css_provider_load_from_path(css, "glade/theme.css", NULL);
    // gtk_style_context_add_provider_for_screen(display, GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_USER);

    g_signal_connect(log_reg.login_window, "destroy", close_window, NULL);
    gtk_builder_connect_signals(log_reg.builder, NULL);
    gtk_widget_grab_focus(log_reg.log_in_button);
    gtk_widget_show(log_reg.login_window);
    gtk_main();

    free(log_reg.username);
    free(log_reg.password);
}
