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


static void showDB_users() {
    int rc = 0;
    char zSql[]="SELECT * FROM users";
    //printf("*** \tShow DB\t ***\n");
    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {
                printf("%d\t%s\t%s\t%s\t%s\t%d\t%s\t%s\n",
                        sqlite3_column_int(stmt,0),
                        sqlite3_column_text(stmt,1),
                        sqlite3_column_text(stmt,2),
                        sqlite3_column_text(stmt,3),
                        sqlite3_column_text(stmt,4),
                        sqlite3_column_int(stmt,5),
                        sqlite3_column_text(stmt,6),
                        sqlite3_column_text(stmt,7));
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA);
}



static void showDB_user_contacts() {
    int rc = 0;
    char zSql[]="SELECT * FROM user_contacts";
    //printf("*** \tShow DB\t ***\n");
    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {
                printf("%d\t %d\n",
                        sqlite3_column_int(stmt,0),
                        sqlite3_column_int(stmt,1));
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA);
}




// const char *id_user(const char *id_chat) { 
//     int rc = 0;
//     char zSql[]="SELECT * FROM contacts";
//     int count = 0;

//     do {
//             sqlite3_prepare(db, zSql, -1, &stmt, 0);
//             while(SQLITE_ROW == sqlite3_step(stmt)) {


//                 printf("%s\n", sqlite3_column_text(stmt,0));

//                 if (strcmp((const char*)sqlite3_column_text(stmt,0), id_chat) == 0 ) {
//                     const char *id = mx_strnew(255);
//                     id = (const char*)sqlite3_column_text(stmt,1);
//                     return id;
//                 }
//             }
//             rc = sqlite3_finalize(stmt);
//         }
//     while(rc == SQLITE_SCHEMA); {}
//     return "-1";
// }







static const char *find_whom_id(char *whom) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM users";

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {


                printf("%s\n", sqlite3_column_text(stmt,1));

                if (strcmp((const char*)sqlite3_column_text(stmt,1), whom) == 0 ) {
                    //printf("нашел нужного юзера\n");
                    //printf("%s\n", sqlite3_column_text(stmt,3));
                    const char *id = mx_strnew(255);
                    id = (const char*)sqlite3_column_text(stmt,0);
                    return id;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    char *err = "-1";
    return err;
}


static const char *friend_contact_id(const char *id_who, int i, int friend) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM user_contacts";
    int count = 0;
    int krugi = 0;

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {


                printf("%s\n", sqlite3_column_text(stmt,0));

                if (strcmp((const char*)sqlite3_column_text(stmt,0), id_who) == 0 ) {
                    krugi++;

                    if(krugi == i) {
                        const char *res = mx_strnew(255);
                        res = (const char*)sqlite3_column_text(stmt,1);
                        return res;
                    }
                }
            }
                rc = sqlite3_finalize(stmt);
                }
    while(rc == SQLITE_SCHEMA); {}
    return "-1";
}


static const char *friend_user_id(const char *id_who) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM contacts";
    int count = 0;

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {


                printf("%s\n", sqlite3_column_text(stmt,0));

                if (strcmp((const char*)sqlite3_column_text(stmt,0), id_who) == 0 ) {
                        const char *res = mx_strnew(255);
                        res = (const char*)sqlite3_column_text(stmt,1);
                        return res;
                }
            }
                rc = sqlite3_finalize(stmt);
                }
    while(rc == SQLITE_SCHEMA); {}
    return "-1";
}





static const char *friend_username(const char *id_who) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM users";
    int count = 0;

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {


                printf("%s\n", sqlite3_column_text(stmt,1));

                if (strcmp((const char*)sqlite3_column_text(stmt,0), id_who) == 0 ) {
                        const char *res = mx_strnew(255);
                        res = (const char*)sqlite3_column_text(stmt,3);
                        return res;
                }
            }
                rc = sqlite3_finalize(stmt);
                }
    while(rc == SQLITE_SCHEMA); {}
    return "-1";
}


char **mx_my_mail(char *who) {
 
 

    startDB();
    showDB_users();
    showDB_user_contacts();
    //showDB_user_contacts();

    const char *id_who = find_whom_id(who);  //получили айди  чувака
    int friends = count_friends(who);   //кол его друзей

    char **arr = NULL;
    arr = malloc(sizeof(char *) * (255));

    int i = 1;
    while(i <= friends) {
        const char *contact_id = friend_contact_id(id_who, i, friends);
        arr[i-1] = mx_strnew(mx_strlen(contact_id));
        arr[i-1] = mx_strcpy(arr[i-1], contact_id);
        arr[i] = NULL;
        i++;
    }

    printf("%s arr[0]\n", arr[0]);
    printf("%s arr[1]\n", arr[1]);
    printf("%s arr[2]\n", arr[2]);

    int z = 0;
    char **user_id = NULL;
    user_id = malloc(sizeof(char *) * (255));
    while(arr[z] != NULL) {
        const char *user_id_num = friend_user_id(arr[z]);
        user_id[z] = mx_strnew(mx_strlen(user_id_num));
        user_id[z] = mx_strcpy(arr[z], user_id_num);
        user_id[z+1] = NULL;
        z++;
    }


    printf("%s user_id[0]\n", user_id[0]);
    printf("%s user_id[1]\n", user_id[1]);
    printf("%s user_id[1]\n", user_id[2]);
    




    int k = 0;
    char **user_name = NULL;
    user_name = malloc(sizeof(char *) * (255));
    while(user_id[k] != NULL) {
        const char *user_id_name = friend_username(user_id[k]);
        user_name[k] = mx_strnew(mx_strlen(user_id_name));
        user_name[k] = mx_strcpy(arr[k], user_id_name);
        user_name[k+1] = NULL;
        //printf("%s user_id_name[]\n", user_id_name);
        k++;
    }




    printf("%s user_id_name[0]\n", user_name[0]);
    printf("%s uuser_id_name[1]\n", user_name[1]);
    printf("%s user_id_name[1]\n", user_name[2]);

return user_name;
    




    //showDB_users();
    //showDB_contacts();
    //showDB_user_contacts();
    endDB();
}
