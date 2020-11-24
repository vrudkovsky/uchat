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

static char *mx_in_search_mail(char *username) {
    int rc = 0;
    char *email = NULL;
    char zSql[]="SELECT * FROM users";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (strcmp((const char*)sqlite3_column_text(stmt,1), username) == 0 ) {
                email = mx_strdup((const char*)sqlite3_column_text(stmt,3));
                break;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while (rc == SQLITE_SCHEMA); {}
    return email;
}

char *in_search_mail(char *username) {
    char *email;

    startDB();
    email = mx_in_search_mail(username);
    endDB();
    return email;
}

