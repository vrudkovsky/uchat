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

static int count_msgs(int chat_id) {
	int rc = 0;
    int count = 0;
    char zSql[] = "SELECT * FROM messages";

    do  {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while(SQLITE_ROW == sqlite3_step(stmt)) {
            if (sqlite3_column_int(stmt,7) ==  chat_id)
 				count++;
        }
        rc = sqlite3_finalize(stmt);
    }
    while(rc == SQLITE_SCHEMA); {}
    return count;
}


int mx_count_sms(int chat_id) {
    int count;

	startDB();
    count = count_msgs(chat_id);
    endDB();

	return count;
}
