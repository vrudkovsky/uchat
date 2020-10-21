#include "server.h"

cJSON * bussines_logic_main(cJSON *j_request, cJSON *j_responce) {
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_request, "action");

    if (strcmp(json_type->valuestring, "login") == 0) {
        j_responce = login_user(j_request, j_responce);
    }    
    else if (strcmp(json_type->valuestring, "register") == 0) {
        j_responce = register_user(j_request, j_responce);
    }
    return j_responce;
}
