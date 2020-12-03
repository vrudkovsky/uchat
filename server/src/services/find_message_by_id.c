
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

static char *mx_sms_chaty_user(int id_message) {
	int rc = 0;
    char *message;
    int i = 0;
    int count = 0;
    char zSql[] = "SELECT * FROM messages";


    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
                if (sqlite3_column_int(stmt,0) == id_message) {
                    message = mx_strdup((const char*)sqlite3_column_text(stmt,3));
                }
        }
        rc = sqlite3_finalize(stmt);
    }
    while (rc == SQLITE_SCHEMA); {}
    return message;
}


char *find_message_by_id(int id_message) {
    char *message;
    startDB();

    message = mx_sms_chaty_user(id_message);

    endDB();
    return message;
}
