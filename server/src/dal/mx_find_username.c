#include "server.h" 
#include <sqlite3.h>

	sqlite3 *db;
	sqlite3_stmt* stmt; // строка запроса к БД

static void startDB() {
    if( sqlite3_open("uchat.db", &db))
        printf("Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
}

static void endDB(){
    sqlite3_close(db);
}

static bool find_username(char *username) { 
	int rc = 0;
    char zSql[]="SELECT * FROM users";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (strcmp((const char*)sqlite3_column_text(stmt,1), username) == 0 ) {
                rc = sqlite3_finalize(stmt);
                return true;
            }
        }
        rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    return false;
}

bool mx_find_username(char *username) {
    bool flag = false;

	startDB();

	if (find_username(username))
        flag = true;
    
    endDB();
    return flag;
}
