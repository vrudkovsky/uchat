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

typedef struct chats_request {
    int chat_id;
    char *interlocutor;
    struct chats_request *next;
}              chat_req_t;

typedef struct chats {
    bool is_owner;
    int msg_id;
    int time;
    char *msg;
    struct chats *next;
}              chats_t;

typedef struct contacts_list {
    char *username;
    char *initials;
    char *email;
    int chat_id;
    chats_t *chats;
    struct contacts_list *next;
}              contact_t;

typedef struct chat_row {
    GtkWidget *row;
    GtkWidget *fixed;
    GtkWidget *username_label;
    GtkWidget *update_box;
    GtkWidget *time_label;
    GtkWidget *you_label;
    GtkWidget *msg_label;
    struct contact_widget *next;
}               chat_row_t;

typedef struct dialog {
    int last_msg_at;
    bool last_msg_owner;
    char *last_msg_text;
    bool updates;
    contact_t *user_info;
    chat_row_t *chat_row;
    struct dialog *next;
}              dialog_t;   

struct main_info {
    int app_status;
    char *username;
    char *initials;
    char *password;
    char *password_conf;
    char *email;
    short sock_fd;
    int contacts;
    dialog_t *dialogs_list;
    contact_t *contact_list;
    chat_req_t *chat_req_list;
}      main_data;

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
    GtkWidget *main_user_initials_label;
    GtkWidget *main_username_label;
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
    GtkWidget *use_search_label;
    GtkWidget *chat_list_box;
    GtkWidget *dont_have_chats_label;
    GtkWidget *chat_search_entry;
    GtkWidget *chat_info_main;
    GtkWidget *msg_entry;
    GtkWidget *send_button;
    GtkWidget *cant_find_chats_label;
    GtkWidget *dialog_list_box;

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

typedef struct message_widget_list {
    GtkWidget *row;

    GtkWidget *main_box;
    GtkWidget *avatar_box;
    GtkWidget *work_box;
    GtkWidget *message_box;
    GtkWidget *control_box;

    GtkWidget *initials_label;
    GtkWidget *msg_label;
    GtkWidget *time_label;

    struct message_widget_list *next;
}              message_widget_t;

struct show_dialog_info {
    GtkWidget *msg_entry;
    GtkWidget *send_button;
    int user_num;
    char *msg_field;
    dialog_t *user;
    message_widget_t *message;
}      dialog_view;

void start_error(int argc, char **argv);
void connection_establisher(unsigned short port, char *ip_address);
void close_window(void);
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
void fill_chats_data(cJSON *responce);
void add_new_chats_in_chats_list(cJSON *chat);
contact_t *search_contact_node(char *contact_name);
void insert_new_message_in_chat(int chat_id, int msg_id, bool is_owner, int time, char *msg);
void updates_logic(char *username);
void insert_new_chat_request(int chat_id, char *interlocutor);

void add_dialog_node_FIFO(contact_t *contact_data);
chats_t *search_last_msg_node(chats_t *chat);
char *time_converter(int seconds, short mode);
void message_row_constructor(message_widget_t *message_gui, bool is_owner, int time, char *msg);

#endif
