#include "client.h"

int result;

void on_username_reg_field_changed(GtkEntry *e) {
    sprintf(log_reg.username, "%s", gtk_entry_get_text(e));
}

void on_email_reg_field_changed(GtkEntry *e) {
    sprintf(log_reg.email, "%s", gtk_entry_get_text(e));
}

void on_password_reg_field_changed(GtkEntry *e) {
    sprintf(log_reg.password, "%s", gtk_entry_get_text(e));
}

void on_password_reg_conf_field_changed(GtkEntry *e) {
    sprintf(log_reg.password_conf, "%s", gtk_entry_get_text(e));
}

void on_username_reg_field_activate(GtkWindow *w) {
    switch (result = reg_request()) {
        case  1:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "you have been registered and logged in"); break;
        case -1:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "please, fill all fields"); break;
        case -2:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "invalid input characters"); break;
        case -3:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "invalid email format"); break;
        case -4:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "passwords do not match"); break;
        case -5:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such username already registered, try another one"); break;
        case -6:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such email already registered, try another one"); break;
        case -7:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such user already registered, please login"); break;
    } 
}

void on_email_reg_field_activate(GtkWindow *w) {
    switch (result = reg_request()) {
        case  1:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "you have been registered and logged in"); break;
        case -1:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "please, fill all fields"); break;
        case -2:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "invalid input characters"); break;
        case -3:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "invalid email format"); break;
        case -4:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "passwords do not match"); break;
        case -5:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such username already registered, try another one"); break;
        case -6:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such email already registered, try another one"); break;
        case -7:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such user already registered, please login"); break;
    } 
}

void on_password_reg_field_activate(GtkWindow *w) {
    switch (result = reg_request()) {
        case  1:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "you have been registered and logged in"); break;
        case -1:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "please, fill all fields"); break;
        case -2:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "invalid input characters"); break;
        case -3:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "invalid email format"); break;
        case -4:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "passwords do not match"); break;
        case -5:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such username already registered, try another one"); break;
        case -6:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such email already registered, try another one"); break;
        case -7:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such user already registered, please login"); break;
    } 
}

void on_password_reg_conf_field_activate(GtkWindow *w) {
    switch (result = reg_request()) {
        case  1: gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "you have been registered and logged in"); break;
        case -1:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "please, fill all fields"); break;
        case -2:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "invalid input characters"); break;
        case -3:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "invalid email format"); break;
        case -4:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "passwords do not match"); break;
        case -5:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such username already registered, try another one"); break;
        case -6:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such email already registered, try another one"); break;
        case -7:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such user already registered, please login"); break;
    } 
}

void on_reg_log_button_clicked(GtkButton *b) {
    switch (result = reg_request()) {
        case  1: gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "you have been registered and logged in"); break;
        case -1:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "please, fill all fields"); break;
        case -2:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "invalid input characters"); break;
        case -3:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "invalid email format"); break;
        case -4:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "passwords do not match"); break;
        case -5:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such username already registered, try another one"); break;
        case -6:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such email already registered, try another one"); break;
        case -7:  gtk_label_set_text(GTK_LABEL(log_reg.reg_error_lable), "such user already registered, please login"); break;
    } 
}
