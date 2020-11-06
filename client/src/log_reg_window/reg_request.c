#include "client.h"

int email_validator(void) {
    int at_count = 0;
    int dot_count = 0;
    int at_position = 0;
    int dot_position = 0;

    for (int i = 0; main_data.email[i]; i++) {
        if (main_data.email[i] == '@') {
            at_count++;
            at_position = i;
        }
        if (main_data.email[i] == '.') {
            dot_count++;
            dot_position = i;
        }
    }
    if (dot_position < at_position)
        return 0;
    if (main_data.email[0] == '@' || main_data.email[mx_strlen(main_data.email - 1)] == '.')
        return 0;
    if (at_count != 1 || dot_count == 0) 
        return 0;
    return 1;
}

int reg_request(void) {
    int flag = 0;
    if (mx_strlen(main_data.username) < 1 || mx_strlen(main_data.password) < 1 || mx_strlen(main_data.email) < 1 || mx_strlen(main_data.password_conf) < 1)
        return -1;
    for (int i = 0; main_data.username[i]; i++)
        if (main_data.username[i] < 32 || main_data.username[i] > 126)
            return -2;
    for (int i = 0; main_data.password[i]; i++)
        if (main_data.password[i] < 32 || main_data.password[i] > 126)
            return -2;
    for (int i = 0; main_data.email[i]; i++)
        if (main_data.email[i] < 32 || main_data.email[i] > 126)
            return -2;
    if (!email_validator())
        return -3;
    if (strcmp(main_data.password, main_data.password_conf) != 0) 
        return -4;

    char *responce1 = mx_strnew(2000);
    cJSON *j_responce = cJSON_CreateObject();
	cJSON *j_register = cJSON_CreateObject();
    cJSON_AddItemToObject(j_register, "action", cJSON_CreateString("register"));
    cJSON_AddItemToObject(j_register, "email", cJSON_CreateString(main_data.email));
    cJSON_AddItemToObject(j_register, "username", cJSON_CreateString(main_data.username));
    cJSON_AddItemToObject(j_register, "password", cJSON_CreateString(main_data.password));
    char *jdata = cJSON_Print(j_register);
    write(main_data.sock_fd, jdata, mx_strlen(jdata));
	cJSON_Delete(j_register);
    free(jdata);
    usleep(100);
    recv(main_data.sock_fd, responce1, 2000, 0);
    j_responce = cJSON_Parse(responce1);
    free(responce1);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "status");
    if(cJSON_IsTrue(json_type)) {
        return 1;
    }
    else {
        json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "usernameexist");
        if(cJSON_IsTrue(json_type))
            flag += 1;
        json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "emailexist");
        if(cJSON_IsTrue(json_type))
            flag += 2;
        switch (flag) {
            case 1: return -5;
            case 2: return -6;
            case 3: return -7;
        }
    }
    return 0;
}
