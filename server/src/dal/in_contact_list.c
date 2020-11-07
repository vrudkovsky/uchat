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



static void showDB_contacts() {
    int rc = 0;
    char zSql[]="SELECT * FROM contacts";
    //printf("*** \tShow DB\t ***\n");
    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {
                printf("%d\t %s\t %s\t %s\t %s\t %d\n",
                        sqlite3_column_int(stmt,0),
                        sqlite3_column_text(stmt,1),
                        sqlite3_column_text(stmt,2),
                        sqlite3_column_text(stmt,3),
                        sqlite3_column_text(stmt,4),
                        sqlite3_column_int(stmt,5));
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



// static bool find_email(char *email) { //затычка либы
//     int rc = 0;
//     printf("\n%s                                 email", email);
//     char zSql[]="SELECT * FROM users";
//     printf("*** \tShow DB\t ***\n");
//     do
//         {
//             sqlite3_prepare(db, zSql, -1, &stmt, 0);

//             while(SQLITE_ROW == sqlite3_step(stmt)) {


//                 printf("%s\n", sqlite3_column_text(stmt,3));

//                 if ( strcmp((const char*)sqlite3_column_text(stmt,3), email) == 0 ) {
//                     printf("<--!!!!! Inside search function !!!!->");

//                     return 1;
//                 }
//             }
//             rc = sqlite3_finalize(stmt);
//         }
//     while(rc == SQLITE_SCHEMA); {}
//     return 0;
// }


static const char *find_whom_id(char *whom) { //находит айди whom
    int rc = 0;
    //printf("\n%s                                 email", whom);
    char zSql[]="SELECT * FROM users";
    //printf("*** \tShow DB\t ***\n");
    do
        {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);

            while(SQLITE_ROW == sqlite3_step(stmt)) {


                printf("%s\n", sqlite3_column_text(stmt,1));

                if (strcmp((const char*)sqlite3_column_text(stmt,1), whom) == 0 ) {
                    //printf("нашел нужного юзера\n");
                    //printf("%s\n", sqlite3_column_text(stmt,3));
                    const char *id = (const char*)sqlite3_column_text(stmt,0);
                    //printf("%s\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! id whom\n", id);
                    return id;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    char *err = "-1";
    return err;
}

static const char *find_contacts_id(const char *id_whom) { //находит айди whom
    int rc = 0;
    //printf("\n%s                                 email", id_whom);
    char zSql[]="SELECT * FROM contacts";
    //printf("*** \tShow DB\t ***\n");
    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);

            while(SQLITE_ROW == sqlite3_step(stmt)) {
                printf("%s\n", sqlite3_column_text(stmt,1));

                if (strcmp((const char*)sqlite3_column_text(stmt,1), id_whom) == 0 ) {
                    printf("нашел id нужного юзера in contacts\n");
                    //printf("%s\n", sqlite3_column_text(stmt,3));
                    const char *id = (const char*)sqlite3_column_text(stmt,0);
                    //printf("%s\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! id_contacts_whom\n", id);
                    return id;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    char *err = "-1";
    return err;
}


static bool find_user_contacts(const char *id_whom, const char *id_contacts_whom) { //находит айди whom
    int rc = 0;
    //printf("\n%s                                 email", id_whom);
    char zSql[]="SELECT * FROM user_contacts";
    //printf("*** \tShow DB\t ***\n");
    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {
                printf("%s\n", sqlite3_column_text(stmt,1));

                if ((strcmp((const char*)sqlite3_column_text(stmt,0), id_whom) == 0 ) && (strcmp((const char*)sqlite3_column_text(stmt,1), id_contacts_whom) == 0 )){
                    printf("есть в друзьях\n");
                    //printf("%s\n", sqlite3_column_text(stmt,3));
                    return true;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    printf("нет в друзьях\n");
    return false;
}



bool in_contact_list(char *who, char *whom) {
    //char *whom = "mdudnyk";
    //char *who = "mdudnyk";

    startDB();
    showDB_users();
    showDB_contacts();
    //showDB_user_contacts();


    const char *id_whom = find_whom_id(whom);  //получили айди 
    //printf("%s\n", id_whom);

    const char *id_contacts_whom = find_contacts_id(id_whom); //получили айди кого по таблице контактс
    //printf("%s\n", id_contacts_whom);

    const char *id_who = find_whom_id(who);  //получили айди 
    //printf("%s\n", id_who);

    if(find_user_contacts(id_who, id_contacts_whom) == true)
        return true;

    //showDB_users();
    //showDB_contacts();
    //showDB_user_contacts();
    endDB();
    return false;
}

// int main() {
//     mx_find_email();
// }
