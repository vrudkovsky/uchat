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

static int *mx_id_msgs(int *arr, int chat_id, int user_id) {
	int rc = 0;
    int i = 0;
    char zSql[]="SELECT * FROM messages";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (sqlite3_column_int(stmt, 7) ==  chat_id) {
                if ((sqlite3_column_int(stmt, 1) ==  user_id) || 
                   ((sqlite3_column_int(stmt, 2) ==  user_id && sqlite3_column_int(stmt, 5) ==  0))) {
                    arr[i] = sqlite3_column_int(stmt, 0);
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

int *get_msgs_ids(int chat_id, int count_sms, char *username) {
    int *arr = malloc(sizeof(int) * (count_sms + 1));
    int user_id;
    arr[count_sms] = -1;

    startDB();
    user_id = find_who_id(username);
    arr = mx_id_msgs(arr, chat_id, user_id);
    endDB();

    return arr;
}
