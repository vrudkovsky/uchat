#include "client.h"

static void registration_check_logic(void) {
    int result = reg_request();
    switch (result) {
        case  1:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "you have been registered"); break;
        case -1:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "please, fill all fields"); break;
        case -2:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "invalid input characters"); break;
        case -3:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "invalid email format"); break;
        case -4:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "passwords do not match"); break;
        case -5:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such username already registered, try another one"); break;
        case -6:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such email already registered, try another one"); break;
        case -7:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such user already registered, please login"); break;
    }
}

void on_username_reg_field_changed(GtkEntry *e) {
    sprintf(main_data.username, "%s", gtk_entry_get_text(e));
}

void on_email_reg_field_changed(GtkEntry *e) {
    sprintf(main_data.email, "%s", gtk_entry_get_text(e));
}

void on_password_reg_field_changed(GtkEntry *e) {
    sprintf(main_data.password, "%s", gtk_entry_get_text(e));
}

void on_password_reg_conf_field_changed(GtkEntry *e) {
    sprintf(main_data.password_conf, "%s", gtk_entry_get_text(e));
}

void on_username_reg_field_activate(GtkWindow *w) {
    registration_check_logic();
}

void on_email_reg_field_activate(GtkWindow *w) {
    registration_check_logic();
}

void on_password_reg_field_activate(GtkWindow *w) {
    registration_check_logic();
}

void on_password_reg_conf_field_activate(GtkWindow *w) {
    registration_check_logic();
}

void on_reg_log_button_clicked(GtkButton *b) {
    registration_check_logic();
}
