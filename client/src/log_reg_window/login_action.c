#include "client.h"

void check_data_logic(void) {
    if (login_request()) {
        gtk_widget_hide(log_reg.login_window);
        gtk_main_quit();
        main_data.app_status = 2;
    }
    else
        gtk_label_set_text(GTK_LABEL(log_reg.login_error_lable), "invalid username or password");    
}

void on_username_field_changed(GtkEntry *e) {
    sprintf(log_reg.username, "%s", gtk_entry_get_text(e));
}

void on_password_field_changed(GtkEntry *e) {
    sprintf(log_reg.password, "%s", gtk_entry_get_text(e));
}

void on_username_field_activate(GtkWindow *w) {
    check_data_logic();
}

void on_password_field_activate(GtkWindow *w) {
    check_data_logic();
}

void on_log_in_button_clicked(GtkWindow *w) {
    check_data_logic();
}
