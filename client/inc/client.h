#ifndef CLIENT_H
#define CLIENT_H

#include "libmx.h"
#include "cJSON.h"
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    char *initials;
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
    GtkWidget *settings_row;
    GtkStack *chats_contacts_stack;
    GtkWidget *chats_list;
    GtkWidget *contacts_list;
    GtkWidget *empty_list;

    GtkWidget *contact_search_entry;
    GtkStack *contact_search_result_stack;
    GtkWidget *contact_search_result_fixed;
    GtkWidget *contact_search_result_empty_fixed;
    GtkWidget *contact_search_result_label;
    GtkWidget *sorry_find_user_label;
    GtkWidget *contact_search_end_button;
    GtkWidget *contact_search_result_list_box;

    GtkWidget *contacts_scrolled_window;
    GtkWidget *contact_list_box;

    GtkStack *main_info_stack;
    GtkWidget *contact_info_empty;

    contact_row_t *contact_row_list;
}       chat;


struct contact_search_row_struct {
    bool user_is_found;
    bool in_contacts;
    bool showing_result;
    contact_t *info;
    contact_row_t *contact_row_list;
}      search_user_data;

struct show_contact_info {
    bool in_contacts;
    bool search_view_is_active;
    GtkWidget *stack_page;
    GtkWidget *initials_label;
    GtkWidget *username_label;
    GtkWidget *email_label;
    GtkWidget *write_message_button;
    GtkWidget *add_contact_button;
    GtkWidget *delete_contact_button;
    contact_t *user_data;
}      contact_info_view;

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
void add_new_contact_row_in_list(char *username, char *initials, int position);
void find_new_contact(char *username);
char *make_initials_by_username(char *username);
void contact_stack_info_init(void);
void print_contact_list(void);
void activate_deactivate_all_rows_in_contact_list(bool switcher);
int search_user_in_local_contact_list(char *username);
void init_contact_row_widgets(contact_row_t *node, char *username, char *initials, GtkWidget *listbox, int position);

#endif
