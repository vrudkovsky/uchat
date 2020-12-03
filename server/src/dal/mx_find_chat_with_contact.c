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

static int search_chat(int who_id, int whom_id) {
	int rc = 0;
    int chat_id = -1;
    char zSql[] = "SELECT * FROM conversations";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if ((sqlite3_column_int(stmt, 1) == who_id && sqlite3_column_int(stmt, 2) == whom_id) ||
                (sqlite3_column_int(stmt, 1) == whom_id && sqlite3_column_int(stmt, 2) == who_id)) {
                chat_id = sqlite3_column_int(stmt, 0);
                break;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while (rc == SQLITE_SCHEMA); {}
    return chat_id;
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

int mx_find_chat_with_contact(char *who, char *whom) {
    int chat_id;
    int who_id;
    int whom_id;

    startDB();
    who_id = find_who_id(who);
    whom_id = find_who_id(whom);
    chat_id = search_chat(who_id, whom_id);
    endDB();

    return chat_id;
}
