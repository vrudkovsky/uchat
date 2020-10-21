#include "client.h"

void log_reg_window(void) {
    gtk_init(NULL, NULL);

    log_reg_widgets();
    log_reg_actions();

    g_signal_connect(log_reg.login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(log_reg.builder, NULL);
    gtk_widget_grab_focus(log_reg.log_in_button);
    gtk_widget_show(log_reg.login_window);
    gtk_main();

    free(log_reg.username);
    free(log_reg.password);
}
