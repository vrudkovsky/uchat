#include "client.h"

//CHATS LIST INIT FUNCTIONS

static void chats_history_send_request(void) {
    cJSON *j_contacts = cJSON_CreateObject();
    char *jdata = NULL;
    cJSON_AddItemToObject(j_contacts, "action", cJSON_CreateString("get chats"));
    cJSON_AddItemToObject(j_contacts, "who", cJSON_CreateString(main_data.username));
    jdata = cJSON_Print(j_contacts);
    printf("client request ->\n%s\n", jdata);
    write(main_data.sock_fd, jdata, mx_strlen(jdata));
	cJSON_Delete(j_contacts);
    free(jdata);
}

static void chats_history_get_responce(void) {
    char *responce = mx_strnew(2000);
    cJSON *j_responce = cJSON_CreateObject();
    recv(main_data.sock_fd, responce, 2000, 0);
    printf("server responce->\n%s\n", responce);
    j_responce = cJSON_Parse(responce);
    free(responce);

    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "status");

    if (cJSON_IsTrue(json_type))
        fill_chats_data(j_responce);
    //print_contact_list();
}


//CONTACT LIST INIT FUNCTIONS

static void print_chat_content(chats_t *chat) {
    chats_t *node = chat;
    while (node != NULL) {
        printf("is owner:\t%d\n", node->is_owner);
        printf("msg id:\t\t%d\n", node->msg_id);
        printf("time:\t\t%d\n", node->time);
        printf("msg:\t\t%s\n\n", node->msg);
        node = node->next;
    }
}

void print_contact_list(void) {
    contact_t *node = main_data.contact_list;
    while (node != NULL) {
        printf("\n\nusername:\t%s\n", node->username);
        print_chat_content(node->chats);
        node = node->next;
    }
}

static void contact_list_send_request(void) {
    cJSON *j_contacts = cJSON_CreateObject();
    char *jdata = NULL;
    cJSON_AddItemToObject(j_contacts, "action", cJSON_CreateString("get contacts"));
    cJSON_AddItemToObject(j_contacts, "who", cJSON_CreateString(main_data.username));
    jdata = cJSON_Print(j_contacts);
    printf("client request ->\n%s\n", jdata);
    write(main_data.sock_fd, jdata, mx_strlen(jdata));
	cJSON_Delete(j_contacts);
    free(jdata);
}

char *make_initials_by_username(char *username) {
    char *initials = mx_strnew(2);
    for (int i = 0; i < 2; i++) {
        if (username[i] > 96 && username[i] < 123) {
            initials[i] = username[i] - 32;
        }
        else
            initials[i] = username[i];
    }
    return initials;
} 

void add_new_contact_data_in_list(char *username, char *email) {
    if (main_data.contact_list == NULL) {
        main_data.contact_list = malloc(sizeof(contact_t));
        main_data.contact_list->username = mx_strdup(username);
        main_data.contact_list->initials = make_initials_by_username(username);
        main_data.contact_list->email = mx_strdup(email);
        main_data.contact_list->chat_id = -1;
        main_data.contact_list->chats = NULL;
        main_data.contact_list->next = NULL;
    } 
    else {
        contact_t *new_node = malloc(sizeof(contact_t));
        new_node->next = main_data.contact_list;
        new_node->username = mx_strdup(username);
        new_node->initials = make_initials_by_username(username);
        new_node->email = mx_strdup(email);
        new_node->chat_id = -1;
        new_node->chats = NULL;
        main_data.contact_list = new_node;
    }
}

static void fill_contact_list(cJSON *j_responce) {
    cJSON *usernames_array = cJSON_GetObjectItemCaseSensitive(j_responce, "username");
    cJSON *emails_array = cJSON_GetObjectItemCaseSensitive(j_responce, "email");
    cJSON *username;
    cJSON *email;

    for (int i = 0; i < main_data.contacts; i++) {
        username = cJSON_GetArrayItem(usernames_array, i);
        email = cJSON_GetArrayItem(emails_array, i);
        add_new_contact_data_in_list(username->valuestring, email->valuestring);
    }
    //print_contact_list();
}

static void contact_list_get_responce(void) {
    char *responce = mx_strnew(2000);
    cJSON *j_test = cJSON_CreateObject();
    cJSON *j_responce = cJSON_CreateObject();
    recv(main_data.sock_fd, responce, 2000, 0);

    printf("server responce->\n%s\n", responce);

    j_responce = cJSON_Parse(responce);
    free(responce);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "status");
    if (cJSON_IsTrue(json_type)) {
        json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "count");
        main_data.contacts = json_type->valueint;
        fill_contact_list(j_responce);
    }
    else 
        main_data.contacts = 0;
}

void start_requests(void) {
    main_data.contact_list = NULL;
    main_data.chat_req_list = NULL;
    main_data.dialogs_list = NULL;
    contact_list_send_request();
    contact_list_get_responce();
    if (main_data.contacts > 0)
        gtk_widget_hide(chat.use_search_label);
    chats_history_send_request();
    chats_history_get_responce();
    if (!(main_data.dialogs_list == NULL))
        gtk_widget_hide(chat.dont_have_chats_label);
}
