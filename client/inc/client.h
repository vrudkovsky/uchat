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

typedef struct contacts_list {
    char *username;
    char *email;
    struct contacts_list *next;
}              contact_t;

struct main_info {
    int app_status;
    char *username;
    char *password;
    char *password_conf;
    char *email;
    short sock_fd;
    int contacts;
    contact_t *contact_list;
}       main_data;

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
}      log_reg;

typedef struct contact_widget {
    GtkWidget *row;
    GtkWidget *fixed;
    GtkWidget *username_label;
    GtkWidget *initials_label;
    GtkWidget *avatar_box;
    struct contact_widget *next;
}              contact_row_t;

struct chat_window {
    GtkWidget *ch_window;
    GtkBuilder *builder;
    GtkWidget *main_list;
    GtkWidget *chats_row;
    GtkWidget *contacts_row;
    GtkStack *chats_contacts_stack;
    GtkWidget *chats_list;
    GtkWidget *contacts_list;
    GtkWidget *contact_list_box;
    GtkStyleContext *context_i_label;
    contact_row_t *contact_row_list;
}       chat;



void start_error(int argc, char **argv);
void connection_establisher(unsigned short port, char *ip_address);

void log_reg_window(void);
void log_reg_widgets(void);
void log_reg_actions(void);
int login_request(void);
int reg_request(void);
void chat_window_main(void);
void chat_window_init(void);
void start_requests(void);
void work_with_contacts(void);
void add_new_contact_data_in_list(char *username, char *email);
void add_new_contact_row_in_list(char *username);

#endif
