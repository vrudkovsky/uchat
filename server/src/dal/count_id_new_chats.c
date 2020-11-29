#include "server.h" 
#include <sqlite3.h>

	sqlite3 *db;
	sqlite3_stmt *stmt;

static void startDB() {
    if (sqlite3_open("uchat.db", &db))
        printf("Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
}

static void endDB(){
    sqlite3_close(db);
}

static int count_new_chats(int user_id) {
	int rc = 0;
    int count = 0;
    char zSql[] = "SELECT * FROM conversations";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if ((sqlite3_column_int(stmt, 2) ==  user_id) && (sqlite3_column_int(stmt, 3) == 1))
                    count++;
        }
        rc = sqlite3_finalize(stmt);
    }
    while (rc == SQLITE_SCHEMA); {}
    return count;
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
    while (rc == SQLITE_SCHEMA); {}
    return id;
}

int count_id_new_chats(char *username) {
    int count;
    int user_id;

	startDB();
    user_id = find_who_id(username);
    count = count_new_chats(user_id);
    endDB();

	return count;
}
