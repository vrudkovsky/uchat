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

static bool insertRecord(int who_id, int whom_id) {
    sqlite3_prepare_v2(db, "INSERT INTO user_contacts (user_id, contact_id) VALUES (?, ?)", -1, &stmt, NULL);
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

bool mx_add_contact(char *who, char *whom) {
    bool flag;

    startDB();
    flag = insertRecord(find_who_id(who), find_who_id(whom));
    endDB();
    return flag;
}
