#include "server.h" 
#include <sqlite3.h>

    sqlite3 *db;
    sqlite3_stmt* stmt;

static void startDB() {
    if (sqlite3_open("uchat.db", &db))
        printf("Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
}

static void endDB(){
    sqlite3_close(db);
}

static bool insertRecord(int who_id, int whom_id) {
    sqlite3_prepare_v2(db, "DELETE FROM user_contacts WHERE user_id = ? AND contact_id = ?", -1, &stmt, NULL);
    if (stmt != NULL) {
        sqlite3_bind_int(stmt, 1, who_id);
        sqlite3_bind_int(stmt, 2, whom_id);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        return true;
    }
    return false;
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

bool mx_delete_contact(char *who, char *whom) {
    int who_id;
    int whom_id;
    bool flag;

    startDB();

    who_id = find_who_id(who);
    whom_id = find_who_id(whom);
    flag = insertRecord(who_id, whom_id);

    endDB();
    return flag;
}
