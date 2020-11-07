#include "client.h"

static void contact_list_send_request(void) {
    cJSON *j_contacts = cJSON_CreateObject();
    char *jdata = NULL;
    cJSON_AddItemToObject(j_contacts, "action", cJSON_CreateString("get contacts"));
    cJSON_AddItemToObject(j_contacts, "who", cJSON_CreateString(main_data.username));
    jdata = cJSON_Print(j_contacts);
    write(main_data.sock_fd, jdata, mx_strlen(jdata));
	cJSON_Delete(j_contacts);
    free(jdata);
}

void add_new_contact_data_in_list(char *username, char *email) {
    if (main_data.contact_list == NULL) {
        main_data.contact_list = malloc(sizeof(contact_t));
        main_data.contact_list->username = mx_strdup(username);
        main_data.contact_list->email = mx_strdup(email);
        main_data.contact_list->next = NULL;
    } 
    else {
        contact_t *new_node = malloc(sizeof(contact_t));
        new_node->next = main_data.contact_list;
        new_node->username = mx_strdup(username);
        new_node->email = mx_strdup(email);
        main_data.contact_list = new_node;
    }
}

void print_list(void) {
    contact_t *node = main_data.contact_list;
    while (node != NULL) {
        printf("%s\t\t%s\n", node->username, node->email);
        node = node->next;
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
    print_list();
}

static void contact_list_get_responce(void) {
    char *responce = mx_strnew(2000);
    cJSON *j_test = cJSON_CreateObject();
    cJSON *j_responce = cJSON_CreateObject();
    // recv(main_data.sock_fd, responce, 2000, 0);
    // j_responce = cJSON_Parse(responce);
//////////////////////////////////////////////////
    cJSON_AddItemToObject(j_test, "status", cJSON_CreateTrue());
    cJSON_AddItemToObject(j_test, "count", cJSON_CreateString("3"));
    cJSON *username = cJSON_CreateArray();
    cJSON_AddItemToArray(username, cJSON_CreateString("vbrykov"));
    cJSON_AddItemToArray(username, cJSON_CreateString("imovchan"));
    cJSON_AddItemToArray(username, cJSON_CreateString("vrudkovsky"));
    cJSON_AddItemToObject(j_test, "username", username);
    cJSON *email = cJSON_CreateArray();
    cJSON_AddItemToArray(email, cJSON_CreateString("vbrykov@gmail.com"));
    cJSON_AddItemToArray(email, cJSON_CreateString("imovchan@gmail.com"));
    cJSON_AddItemToArray(email, cJSON_CreateString("vrudkovsky@gmail.com"));
    cJSON_AddItemToObject(j_test, "email", email);
    responce = cJSON_Print(j_test);
    //printf("json ->\n%s\n", responce);
    j_responce = cJSON_Parse(responce);
//////////////////////////////////////////////////
    //free(responce);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "status");
    if (cJSON_IsTrue(json_type)) {
        json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "count");
        main_data.contacts = mx_atoi(json_type->valuestring);
        fill_contact_list(j_responce);
    }
    else 
        main_data.contacts = 0;
}

void start_requests(void) {
    main_data.contact_list = NULL;
    usleep(100);
    contact_list_send_request();
    usleep(100);
    contact_list_get_responce();
}
