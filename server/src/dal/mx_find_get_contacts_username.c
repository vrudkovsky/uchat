#include "server.h" 
#include <sqlite3.h>

    sqlite3 *db;
    sqlite3_stmt* stmt; // строка запроса к БД

static void startDB() {
    if (sqlite3_open("uchat.db", &db))
        printf("Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
}

static void endDB(){
    sqlite3_close(db);
}

static int find_who_id(char *who) { //находит айди whom
    int rc = 0;
    int id = -1;
    char zSql[]= "SELECT * FROM users";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (strcmp((const char*)sqlite3_column_text(stmt,1), who) == 0 ) {
                id = sqlite3_column_int(stmt, 0);
                rc = sqlite3_finalize(stmt);
                return id;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while(rc == SQLITE_SCHEMA); {}
    return id;
}


static bool have_friends(int id_who) {
    int rc = 0;
    char zSql[]="SELECT * FROM user_contacts";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while(SQLITE_ROW == sqlite3_step(stmt)) {
            if (sqlite3_column_int(stmt, 0) == id_who) {
                rc = sqlite3_finalize(stmt);
                return true;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while(rc == SQLITE_SCHEMA); {}
    return false;
}

bool mx_find_get_contacts_username(char *who) {
    int id_who;
    bool flag = false;

    startDB();
    id_who = find_who_id(who);

    if (have_friends(id_who))
        flag = true;

    endDB();
    return flag;
}
