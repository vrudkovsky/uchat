#include "server.h" 
#include <sqlite3.h>

    sqlite3 *db;
    sqlite3_stmt* stmt;

static void startDB() {
    int rc = sqlite3_open("uchat.db", &db);

    if (rc)
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
}

static void endDB() {
    sqlite3_close(db);
}

bool check_chat_by_id(int chat_id) {
    bool flag = false;
    int rc = 0;
    char zSql[]= "SELECT * FROM conversations";

    startDB();
    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (sqlite3_column_int(stmt, 0) == chat_id) {
                flag = true;
                break;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while(rc == SQLITE_SCHEMA); {}
    endDB();

    return flag;
}
