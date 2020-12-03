#include "server.h" 
#include <sqlite3.h>

    sqlite3 *db;
    sqlite3_stmt* stmt;

static void startDB() {
    if (sqlite3_open("uchat.db", &db))
        printf("Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
}

static void endDB() {
    sqlite3_close(db);
}

int find_last_chat_id(void) {
    int rc = 0;
    int id = 0;
    char zSql[]= "SELECT * FROM conversations";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt))
            id = sqlite3_column_int(stmt, 0);
        rc = sqlite3_finalize(stmt);
    }
    while(rc == SQLITE_SCHEMA); {}
    return id;
}

static bool insertRecord(int creator_id, int acceptor_id) {
    sqlite3_prepare_v2(db, "INSERT INTO conversations (creator, acceptor) VALUES (?, ?)", -1, &stmt, NULL);
    if (stmt != NULL) {
        sqlite3_bind_int(stmt, 1, creator_id);
        sqlite3_bind_int(stmt, 2, acceptor_id);
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

int mx_create_new_chat(char *who, char *whom) {
    int chat_id = -1;
    int creator_id;
    int acceptor_id;

    startDB();
    creator_id = find_who_id(who);
    acceptor_id = find_who_id(whom);
    if (insertRecord(creator_id, acceptor_id))
        chat_id = find_last_chat_id();
    endDB();

    return chat_id;
}
