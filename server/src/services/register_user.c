#include "server.h" 

cJSON *register_user(cJSON *j_request, cJSON *j_responce) {
    char *username;
    char *password;
    char *email;
    bool flag = true;
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_request, "username");

    if(mx_find_username(json_type->valuestring) != 0) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
        cJSON_AddItemToObject(j_responce, "usernameexist", cJSON_CreateTrue());
        flag = false;
    }

    json_type = cJSON_GetObjectItemCaseSensitive(j_request, "email");
    if(mx_find_email(json_type->valuestring) != 0) {
        if(flag)
            cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
        cJSON_AddItemToObject(j_responce, "emailexist", cJSON_CreateTrue());
        flag = false;
    }

    if (flag == true) {
        json_type = cJSON_GetObjectItemCaseSensitive(j_request, "email");
        username = mx_strcpy(username = mx_strnew(mx_strlen(json_type->valuestring)), json_type->valuestring);
        json_type = cJSON_GetObjectItemCaseSensitive(j_request, "username");
        email = mx_strcpy(email = mx_strnew(mx_strlen(json_type->valuestring)), json_type->valuestring);
        json_type = cJSON_GetObjectItemCaseSensitive(j_request, "password");
        password = mx_strcpy(password = mx_strnew(mx_strlen(json_type->valuestring)), json_type->valuestring);
        mx_create_username_password_login(username, password, email);
        free(email);
        free(username);
        free(password);
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());
    }

    return j_responce;
}
