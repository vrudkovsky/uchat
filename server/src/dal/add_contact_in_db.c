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







static const char *find_whom_id(const char *whom) { //находит айди whow in contacts
    int rc = 0;
    char zSql[]="SELECT * FROM contacts";

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);

            while(SQLITE_ROW == sqlite3_step(stmt)) {


                printf("%s\n", sqlite3_column_text(stmt,1));

                if (strcmp((const char*)sqlite3_column_text(stmt,1), whom) == 0 ) {
                    //printf("нашел нужного юзера\n");
                    //printf("%s\n", sqlite3_column_text(stmt,3));
                    const char *id = (const char*)sqlite3_column_text(stmt,0);
                    return id;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    char *err = "-1";
    return err;
}


static const char *friend_id(const char *whom) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM users";
    int count = 0;

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {

                //printf("%s\n", sqlite3_column_text(stmt,0));

                if (strcmp((const char*)sqlite3_column_text(stmt,1), whom) == 0 ) {
                    const char *id = (const char*)sqlite3_column_text(stmt,0);
                    return id;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    return "-1";
}



static bool insertRecord(const char *str_1, const char *str_2) {

    char *string_1 = "INSERT INTO user_contacts (user_id, contact_id) VALUES ('";
    const char *string_2 = str_1;
    char *string_3 = "', '";
    const char *string_4 = str_2;
    char *string_5 = "')";

    char *srt_buf = mx_strnew(1000);
    srt_buf = strcat(srt_buf, string_1);
    srt_buf = strcat(srt_buf, string_2);
    srt_buf = strcat(srt_buf, string_3);
    srt_buf = strcat(srt_buf, string_4);
    srt_buf = strcat(srt_buf, string_5);
    
     //printf("stroka %s\n", srt_buf);    

     //printf("*** \tInsert into DB\t ***\n");
     sqlite3_prepare(db, srt_buf, -1, &stmt, 0);
     sqlite3_step(stmt);
     return 0;
}







bool mx_add_contact(char *who, char *whom) {
    startDB();
     showDB_users();
    // showDB_contacts();
     showDB_user_contacts();
//printf("id_whom, id_whom");
    const char *id_whom = friend_id(whom);  //получили айди 
    const char *id_who = friend_id(who);  //получили айди
    const char *id_whow_in_contacts = find_whom_id(id_whom);
    insertRecord(id_who, id_whow_in_contacts);

    //printf("%s\n id_whom", id_whom);

    //friend_id(id_whom);
        //return count;


    //showDB_users();
    //showDB_contacts();
    //showDB_user_contacts();
    endDB();
    return true;
}

// int main() {
//     mx_find_email();
// }
