#include "client.h"

void on_username_field_changed(GtkEntry *e) {
    sprintf(log_reg.username, "%s", gtk_entry_get_text(e));
}

void on_password_field_changed(GtkEntry *e) {
    sprintf(log_reg.password, "%s", gtk_entry_get_text(e));
}

void on_username_field_activate(GtkWindow *w) {
    if (login_request())
        gtk_label_set_text(GTK_LABEL(log_reg.login_error_lable), "you're logged in");
    else
        gtk_label_set_text(GTK_LABEL(log_reg.login_error_lable), "invalid username or password");    
}

void on_password_field_activate(GtkWindow *w) {
    if (login_request())
        gtk_label_set_text(GTK_LABEL(log_reg.login_error_lable), "you're logged in");
    else
        gtk_label_set_text(GTK_LABEL(log_reg.login_error_lable), "invalid username or password");
}

void on_log_in_button_clicked(GtkButton *b) {
    if (login_request())
        gtk_label_set_text(GTK_LABEL(log_reg.login_error_lable), "you're logged in");
    else
        gtk_label_set_text(GTK_LABEL(log_reg.login_error_lable), "invalid username or password");
}
