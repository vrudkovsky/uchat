#include "client.h"

void log_reg_actions(void) {
    main_data.username = mx_strnew(20);
    main_data.email = mx_strnew(20);
    main_data.password_conf = mx_strnew(20);
    main_data.password = mx_strnew(20);
}

void on_event_button_release_event(GtkEntry *e) {
    gtk_stack_set_visible_child(log_reg.stack, log_reg.box_2);
    gtk_widget_grab_focus(log_reg.reg_log_button);
}

void on_event2_button_release_event(GtkEntry *e) {
    gtk_stack_set_visible_child(log_reg.stack, log_reg.box_1);
}
