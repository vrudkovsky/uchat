#ifndef CLIENT_H
#define CLIENT_H

#include "libmx.h"
#include "cJSON.h"
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <netdb.h>
#include <errno.h>

struct chat_window {
    GtkWidget *ch_window;
    GtkBuilder *builder;
    GtkStack *chats_contacts_stack;
    GtkWidget *contacts_list;
    GtkWidget *chats_list;
}           chat;

struct main_info {
    int app_status;
}           main_data;

struct start_window {
    GtkBuilder *builder;
    GtkWidget *login_window;
    GtkStack *stack;
    GtkWidget *box_1;
    GtkWidget *username_field;
    GtkWidget *password_field;
    GtkWidget *login_error_lable;
    GtkWidget *log_in_button;
    GtkWidget *box_2;
    GtkWidget *username_reg_field;
    GtkWidget *email_reg_field;
    GtkWidget *password_reg_create_field;
    GtkWidget *password_reg_conf_field;
    GtkWidget *reg_error_lable;
    GtkWidget *reg_log_button;
    char *username;
    char *password;
    char *password_conf;
    char *email;
    short sock_fd;
}              log_reg;

void start_error(int argc, char **argv);
void connection_establisher(unsigned short port, char *ip_address);

void log_reg_window(void);
void log_reg_widgets(void);
void log_reg_actions(void);
int login_request(void);
int reg_request(void);
void chat_window(void);


#endif
