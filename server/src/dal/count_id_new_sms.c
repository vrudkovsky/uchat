#include "server.h" 
#include <sqlite3.h>

	sqlite3 *db;
	sqlite3_stmt* stmt;
    sqlite3_stmt* stmt_1;

static void startDB() {
    if (sqlite3_open("uchat.db", &db))
        printf("Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
}

static void endDB(){
    sqlite3_close(db);
}

static bool new_chat_status_active(int chat_id) {
    int rc = 0;
    char zSql[] = "SELECT * FROM conversations";
    bool flag = false;

    do {
        sqlite3_prepare(db, zSql, -1, &stmt_1, 0);
        while(SQLITE_ROW == sqlite3_step(stmt_1)) {
            if ((sqlite3_column_int(stmt_1, 0) == chat_id) && (sqlite3_column_int(stmt_1, 3) == 1)) {
                flag = true;
                break;
            }
        }
        rc = sqlite3_finalize(stmt_1);
    }
    while(rc == SQLITE_SCHEMA); {}
    return flag;
}

static int count_new_msg(int user_id) {
	int rc = 0;
    int count = 0;
    char zSql[] = "SELECT * FROM messages";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if ((sqlite3_column_int(stmt, 2) ==  user_id) && (sqlite3_column_int(stmt, 5) == 1)) {
                if (!new_chat_status_active(sqlite3_column_int(stmt, 7)))
                    count++;
            }
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

int count_id_new_sms(char *username) {
    int count;
    int user_id;

	startDB();
    user_id = find_who_id(username);
    count = count_new_msg(user_id);
    endDB();

	return count;
}
