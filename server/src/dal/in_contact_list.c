#include "server.h" 
#include <sqlite3.h>

    sqlite3 *db;
    sqlite3_stmt* stmt;

static void startDB() {
    if( sqlite3_open("uchat.db", &db))
        printf("Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
}

static void endDB(){
    sqlite3_close(db);
}

static bool find_user_in_contacts(int id_who, int id_whom) {
    int rc = 0;
    char zSql[]="SELECT * FROM user_contacts";
    bool flag = false;

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while(SQLITE_ROW == sqlite3_step(stmt)) {
            if ((sqlite3_column_int(stmt,0) == id_who) && (sqlite3_column_int(stmt,1) == id_whom)) {
                flag = true;
                break;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while(rc == SQLITE_SCHEMA); {}
    return flag;
}

static int find_who_id(char *who) {
    int rc = 0;
    int id = -1;
    char zSql[]= "SELECT * FROM users";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (strcmp((const char*)sqlite3_column_text(stmt,1), who) == 0 ) {
                id = sqlite3_column_int(stmt, 0);
                break;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while(rc == SQLITE_SCHEMA); {}
    return id;
}

bool in_contact_list(char *who, char *whom) {
    int id_who;
    int id_whom;
    bool flag = false;

    startDB();

    id_who = find_who_id(who);
    id_whom = find_who_id(whom);

    if (find_user_in_contacts(id_who, id_whom))
        flag = true;
    endDB();
    return flag;
}
