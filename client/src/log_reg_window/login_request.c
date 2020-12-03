#include "client.h"

int login_request(void) {
    char *responce = mx_strnew(2000);

    if (mx_strlen(main_data.username) < 1 || mx_strlen(main_data.password) < 1)
        return 0;
    for (int i = 0; main_data.username[i]; i++)
        if (main_data.username[i] < 32 || main_data.username[i] > 126)
            return 0;
    for (int i = 0; main_data.password[i]; i++)
        if (main_data.password[i] < 32 || main_data.password[i] > 126)
            return 0;

	cJSON *j_login = cJSON_CreateObject();
    cJSON *j_responce = cJSON_CreateObject();
    cJSON_AddItemToObject(j_login, "action", cJSON_CreateString("login"));
    cJSON_AddItemToObject(j_login, "username", cJSON_CreateString(main_data.username));
    cJSON_AddItemToObject(j_login, "password", cJSON_CreateString(main_data.password));
    char *jdata = cJSON_Print(j_login);
    write(main_data.sock_fd, jdata, mx_strlen(jdata));
	cJSON_Delete(j_login);
    free(jdata);
    usleep(100);
    recv(main_data.sock_fd, responce, 2000, 0);
    j_responce = cJSON_Parse(responce);
    free(responce);
    
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "status");
    if (cJSON_IsTrue(json_type))
        return 1;
    return 0;
}
