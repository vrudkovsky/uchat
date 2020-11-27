#include "server.h"
#include "cJSON.h"

cJSON * bussines_logic_main(cJSON *j_request, cJSON *j_responce) {
cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_request, "action");

    if (strcmp(json_type->valuestring, "login") == 0) {
        j_responce = login_user(j_request, j_responce);
    }    
    else if (strcmp(json_type->valuestring, "register") == 0) {
        j_responce = register_user(j_request, j_responce);
    }
    else if (strcmp(json_type->valuestring, "find user") == 0) {
        j_responce = find_user(j_request, j_responce);
    }
    else if (strcmp(json_type->valuestring, "get contacts") == 0) {
        j_responce = get_contacts(j_request, j_responce);
    }
    else if (strcmp(json_type->valuestring, "add contact") == 0) {
        j_responce = add_contact(j_request, j_responce);
    }
    else if (strcmp(json_type->valuestring, "delete contact") == 0) {
        j_responce = delete_contact(j_request, j_responce);
    }
    else if (strcmp(json_type->valuestring, "get chats") == 0) {
        j_responce = download_message_history(j_request, j_responce);
    }
    else if (strcmp(json_type->valuestring, "get chat") == 0) {
        j_responce = get_chat(j_request, j_responce);
    }
    else if (strcmp(json_type->valuestring, "create chat") == 0) {
        j_responce = create_new_chat(j_request, j_responce);
    }
    // else if (strcmp(json_type->valuestring, "send message") == 0) { //обработка нового сообщения
    //     j_responce = smsq(j_request, j_responce);
    // }
    // else if (strcmp(json_type->valuestring, "sms") == 0) { //отправить смс
    //     //j_responce = sms(j_request, j_responce);
    //     //printf("%s\n", "sms");
    // }

    //char *jdata = cJSON_Print(j_responce);
    //printf("\n%s\n", jdata);
    return j_responce;
}
