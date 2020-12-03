#include "server.h"

cJSON *get_contacts(cJSON *j_request, cJSON *j_responce) {
    int count = 0;
    int num = 0;
    char **contact_names;
    char **contact_emails;

    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_request, "who");

    if (mx_find_get_contacts_username(json_type->valuestring)) {
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateTrue());

        count = count_friends(json_type->valuestring);
        cJSON_AddItemToObject(j_responce, "count", cJSON_CreateNumber(count));
    
        contact_names = mx_my_username(json_type->valuestring);
        cJSON *j_username_arr = cJSON_CreateArray();
        while(contact_names[num] != NULL) {
            cJSON_AddItemToObject(j_username_arr, "username", cJSON_CreateString(contact_names[num]));
            num++;
        }
        cJSON_AddItemToObject(j_responce, "username", j_username_arr);

        num = 0;
        contact_emails = mx_my_mail(json_type->valuestring);
        cJSON *j_mail_arr = cJSON_CreateArray();
        while(contact_emails[num] != NULL) {
            cJSON_AddItemToObject(j_mail_arr, "email", cJSON_CreateString(contact_emails[num]));
            num++;
        }
        cJSON_AddItemToObject(j_responce, "email", j_mail_arr);
    }
    else 
        cJSON_AddItemToObject(j_responce, "status", cJSON_CreateFalse());
    return j_responce;
}
