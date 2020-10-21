#include "client.h"

void log_reg_widgets(void) {
    log_reg.builder = gtk_builder_new();
    log_reg.builder = gtk_builder_new_from_file("glade/Authentication_window.glade");
    log_reg.login_window = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "login_window"));
    log_reg.stack = GTK_STACK(gtk_builder_get_object (log_reg.builder, "stack"));

    log_reg.box_1 = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "box_1"));
    log_reg.username_field = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "username_field"));
    log_reg.password_field = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "password_field"));
    log_reg.login_error_lable = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "login_error_lable"));
    log_reg.log_in_button = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "log_in_button"));

    log_reg.box_2 = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "box_2"));
    log_reg.username_reg_field = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "username_reg_field"));
    log_reg.email_reg_field = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "email_reg_field"));
    log_reg.password_reg_create_field = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "password_reg_create_field"));
    log_reg.password_reg_conf_field = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "password_reg_conf_field"));
    log_reg.reg_error_lable = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "reg_error_lable"));
    log_reg.reg_log_button = GTK_WIDGET(gtk_builder_get_object(log_reg.builder, "reg_log_button"));
}
