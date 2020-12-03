#include "server.h"
#include "cJSON.h"

cJSON * bussines_logic_main(cJSON *j_request, cJSON *j_responce) {
cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_request, "action");


    if (strcmp(json_type->valuestring, "update") == 0) {
        j_responce = updates_main(j_request, j_responce);
    }
    else if (strcmp(json_type->valuestring, "send msg") == 0) {
        j_responce = send_msg(j_request, j_responce);
    }
    else if (strcmp(json_type->valuestring, "login") == 0) {
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
    // else if (strcmp(json_type->valuestring, "get chat") == 0) {
    //     j_responce = get_chat(j_request, j_responce);
    // }
    else if (strcmp(json_type->valuestring, "create chat") == 0) {
        j_responce = create_new_chat(j_request, j_responce);
    }
    else if (strcmp(json_type->valuestring, "delete sms") == 0) {
        j_responce = mx_delete_sms(j_request, j_responce);
    }
    // else if (strcmp(json_type->valuestring, "update_sms") == 0) {
    //     j_responce = mx_update_sms(j_request, j_responce);
    // }
    return j_responce;
}
