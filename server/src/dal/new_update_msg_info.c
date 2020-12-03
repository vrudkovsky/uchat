
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

static int *mx_id_chaty_user(int user_id, int *arr) {
	int rc = 0;
    int i = 0;
    int count = 0;
    char zSql[] = "SELECT * FROM messages";
    int creator = 0;
    int acceptor = 0;

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if ((sqlite3_column_int(stmt, 2) ==  user_id) && (sqlite3_column_int(stmt, 5) == 1)) {
                if (!new_chat_status_active(sqlite3_column_int(stmt, 7))) {
                    arr[i] = sqlite3_column_int(stmt,7);
                    i++;
                    arr[i] = sqlite3_column_int(stmt,0);
                    i++;
                    arr[i] = sqlite3_column_int(stmt,6);
                    i++;
                }
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while (rc == SQLITE_SCHEMA); {}
    return arr;
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

int *new_update_msgs_info(char *who, int num) {
    int who_id;
    int *arr = malloc(sizeof(int) * (num) *3);

    startDB();
    who_id = find_who_id(who);
    arr = mx_id_chaty_user(who_id, arr);

    endDB();
    return arr;
}

