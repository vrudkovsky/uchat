#include "server.h" 
#include <sqlite3.h>

    sqlite3 *db;
    sqlite3_stmt* stmt; // строка запроса к БД


static void startDB() {
    char str[1000];
    // int lenstr=0;
    if( sqlite3_open("uchat.db", &db)) {
        printf(str, "Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
    }
}

static void endDB(){
    sqlite3_close(db);
}

static const char *find_whom_id(char *whom) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM users";

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {


                //printf("%s\n", sqlite3_column_text(stmt,1));

                if (strcmp((const char*)sqlite3_column_text(stmt,1), whom) == 0 ) {
                    //printf("нашел нужного юзера\n");
                    //printf("%s\n", sqlite3_column_text(stmt,3));
                    const char *id = mx_strnew(255);
                    id = (const char*)sqlite3_column_text(stmt,0);
                    rc = sqlite3_finalize(stmt);
                    return id;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    char *err = "-1";
    return err;
}

static const char *contact_id_message(const char *id_who, const char *id_whom, int i) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM messages";
    int count = 0;
    int krugi = -1;

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {


                //printf("%s\n", sqlite3_column_text(stmt,0));

                if ((strcmp((const char*)sqlite3_column_text(stmt,1), id_who) == 0 ) && (strcmp((const char*)sqlite3_column_text(stmt,2), id_whom) == 0 ))
                    krugi++;

                if ((strcmp((const char*)sqlite3_column_text(stmt,1), id_whom) == 0 ) && (strcmp((const char*)sqlite3_column_text(stmt,2), id_who) == 0 ))
                    krugi++;

                    if(krugi == i) {
                        const char *res = mx_strnew(255);
                        res = (const char*)sqlite3_column_text(stmt,1);
                        rc = sqlite3_finalize(stmt);
                        return res;
                    }
            }
                rc = sqlite3_finalize(stmt);
                }
    while(rc == SQLITE_SCHEMA); {}
    return "-1";
}


static char *who_id(char *whom) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM users";

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {


                //printf("%s\n", sqlite3_column_text(stmt,1));

                if (strcmp((const char*)sqlite3_column_text(stmt,0), whom) == 0 ) {
                    //printf("нашел нужного юзера\n");
                    //printf("%s\n", sqlite3_column_text(stmt,3));
                    char *id = mx_strnew(255);
                    id = (char*)sqlite3_column_text(stmt,1);
                    rc = sqlite3_finalize(stmt);
                    return id;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    char *err = "-1";
    return err;
}


char **mx_get_who(char *who, char *whom, int count_sms) {

    startDB();
    //showDB_users();
    //showDB_user_contacts();
    //showDB_user_contacts();

    const char *friends_1 = find_whom_id(who);   //получили айди  чувака 1
    const char *friends_2 = find_whom_id(whom); //получили айди  чувака 2

    //printf("friends_1 %s\n", friends_1);
    //printf("friends_2 %s\n", friends_2);

    char **arr = NULL;
    arr = malloc(sizeof(char *) * (255));

    int i = 0;
    while(i <= count_sms) {
        const char *id_message = contact_id_message(friends_1, friends_2, i);
       // printf("id_message%s\n", id_message);
        arr[i] = mx_strnew(mx_strlen(id_message));
        arr[i] = mx_strcpy(arr[i], id_message);
        arr[i+1] = NULL;
        i++;
    }

    i = 0;
    while(arr[i] != NULL) {
        arr[i] = who_id(arr[i]);
        i++;
    }

    //printf("arr[0] %s\n", arr[0]);
    // int z = 0;
    // char **user_id = NULL;
    // user_id = malloc(sizeof(char *) * (255));
    // while(arr[z] != NULL) {
    //     const char *user_id_num = friend_user_id(arr[z]);
    //     user_id[z] = mx_strnew(mx_strlen(user_id_num));
    //     user_id[z] = mx_strcpy(arr[z], user_id_num);
    //     user_id[z+1] = NULL;
    //     z++;
    // }


    // printf("%s user_id[0]\n", user_id[0]);
    // printf("%s user_id[1]\n", user_id[1]);
    // printf("%s user_id[1]\n", user_id[2]);
    




    // int k = 0;
    // char **user_name = NULL;
    // user_name = malloc(sizeof(char *) * (255));
    // while(user_id[k] != NULL) {
    //     const char *user_id_name = friend_username(user_id[k]);
    //     user_name[k] = mx_strnew(mx_strlen(user_id_name));
    //     user_name[k] = mx_strcpy(arr[k], user_id_name);
    //     user_name[k+1] = NULL;
    //     //printf("%s user_id_name[]\n", user_id_name);
    //     k++;
    // }




    // printf("%s user_id_name[0]\n", user_name[0]);
    // printf("%s uuser_id_name[1]\n", user_name[1]);
    // printf("%s user_id_name[1]\n", user_name[2]);
    endDB();
    return arr;
    




    //showDB_users();
    //showDB_contacts();
    //showDB_user_contacts();
}
