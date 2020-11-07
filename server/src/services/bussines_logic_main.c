#include "server.h"
#include "cJSON.h"

cJSON * bussines_logic_main(cJSON *j_request, cJSON *j_responce) {
cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_request, "action");

//начало обнов начиная с find_user

    if (strcmp(json_type->valuestring, "login") == 0) {
        j_responce = login_user(j_request, j_responce);
        printf("%s\n", "login");
    }    
    else if (strcmp(json_type->valuestring, "register") == 0) {
        j_responce = register_user(j_request, j_responce);
        printf("%s\n", "login");
    }
    else if (strcmp(json_type->valuestring, "find_user") == 0) {
        j_responce = find_user(j_request, j_responce);
        printf("%s\n", "find_user");
    }
    else if (strcmp(json_type->valuestring, "get_contacts") == 0) {
        j_responce = get_contacts(j_request, j_responce);
        printf("%s\n", "get_contacts");
    }

    else if (strcmp(json_type->valuestring, "add_contact") == 0) {
        j_responce = add_contact(j_request, j_responce);
        printf("%s\n", "add_contact");
    }
    else if (strcmp(json_type->valuestring, "delete_contact") == 0) {
        j_responce = delete_contact(j_request, j_responce);
        printf("%s\n", "delete_contact");
    }


    char *jdata = cJSON_Print(j_responce);
    printf("\n%s\n", jdata);
    return j_responce;
}
