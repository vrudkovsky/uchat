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







static const char *find_whom_id(char *whom) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM users";

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


static bool friend(const char *id_who) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM user_contacts";

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {


                printf("%s\n", sqlite3_column_text(stmt,0));

                if (strcmp((const char*)sqlite3_column_text(stmt,0), id_who) == 0 ) {
                    return true;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    return false;
}





bool mx_find_get_contacts_username(char *who) {
    //char *whom = "mdudnyk";
    //char *who = "mdudnyk";

    startDB();
    showDB_users();
    showDB_user_contacts();
    //showDB_user_contacts();

    const char *id_who = find_whom_id(who);  //получили айди 
    printf("%s\n", id_who);

    if(friend(id_who) == true)
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
