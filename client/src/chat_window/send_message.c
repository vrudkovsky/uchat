#include "client.h"

void insert_new_message_in_chat(int chat_id, int msg_id, char *sender, int time, char *msg) {

}

static int send_message_get_responce() {
    char *responce = mx_strnew(2000);
    cJSON *j_test = cJSON_CreateObject();
    cJSON *create_new_chat = cJSON_CreateObject();

    recv(main_data.sock_fd, responce, 2000, 0);

    printf("server responce->\n%s\n", responce);

    create_new_chat = cJSON_Parse(responce);
    free(responce);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(create_new_chat, "status");

    if (cJSON_IsTrue(json_type)) {
        json_type = cJSON_GetObjectItemCaseSensitive(create_new_chat, "msg id");
        return json_type->valueint;
    }
    return -1;
}

static void send_message_send_request(char *username, char *contact_name, int chat_id, int time, char *msg) {
    cJSON *send_message = cJSON_CreateObject();
    char *jdata = NULL;

    cJSON_AddItemToObject(send_message, "action", cJSON_CreateString("send message"));
    cJSON_AddItemToObject(send_message, "who", cJSON_CreateString(username));
    cJSON_AddItemToObject(send_message, "whom", cJSON_CreateString(contact_name));
    cJSON_AddItemToObject(send_message, "chat id", cJSON_CreateNumber(chat_id));
    cJSON_AddItemToObject(send_message, "time", cJSON_CreateNumber(time));
    cJSON_AddItemToObject(send_message, "msg", cJSON_CreateString(msg));
    
    jdata = cJSON_Print(send_message);
    write(main_data.sock_fd, jdata, mx_strlen(jdata));

    printf("client request->\n%s\n", jdata);

	cJSON_Delete(send_message);
    free(jdata);
}

static void send_message(void) {
    int msg_id;
    int creation_time = time(NULL);
    char *sender = "mdundyk";
    char *recipient = "vbrykov";
    int chat_id = 2;
    char *msg = "How are you?";

    send_message_send_request(sender, recipient, chat_id, creation_time, msg);
    msg_id = send_message_get_responce();
    if (msg_id != -1)
        insert_new_message_in_chat(chat_id, msg_id, sender, creation_time, msg);
}

void on_send_message_field_activated(GtkButton *b) {
    send_message();
}

void on_send_message_button_clicked(GtkButton *b) {
    send_message();
}
