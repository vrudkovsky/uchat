#include "server.h" 
#include <sqlite3.h>

	sqlite3 *db;
	sqlite3_stmt *stmt;

static void startDB() {
    if( sqlite3_open("uchat.db", &db))
        printf("Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
}

static void endDB(){
    sqlite3_close(db);
}

static char *interlocutor_name(int id_who, char *username) {
    int rc = 0;
    char zSql[] = "SELECT * FROM users";
    int count = 0;

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (sqlite3_column_int(stmt,0) == id_who) {
                username = mx_strdup((const char*)sqlite3_column_text(stmt,1));
                break;
            }
        }
        rc = sqlite3_finalize(stmt);
        }
    while (rc == SQLITE_SCHEMA); {}
    return username;
}

static int find_interlocutor(int chat_id, int user_id) {
    int rc = 0;
    int interlocutor_id = -1;
    char zSql[] = "SELECT * FROM conversations";
    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (sqlite3_column_int(stmt,0) == chat_id) {
                if (sqlite3_column_int(stmt,1) == user_id) {
                    interlocutor_id = sqlite3_column_int(stmt,2);
                }
                else
                    interlocutor_id = sqlite3_column_int(stmt,1);
                break;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while(rc == SQLITE_SCHEMA); {}
    return interlocutor_id;
}

static int find_who_id(char *who) {
    int rc = 0;
    int id = -1;
    char zSql[] = "SELECT * FROM users";

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
    while (rc == SQLITE_SCHEMA); {}
    return id;
}

char *mx_search_interlocutor(int id_chat, char *username) {
    char *result = NULL;
    int user_id;
    int interlocutor_id = -1;
    
	startDB();
    user_id = find_who_id(username);
    interlocutor_id = find_interlocutor(id_chat, user_id);
    result = interlocutor_name(interlocutor_id, result);
    endDB();

    return result;
}
