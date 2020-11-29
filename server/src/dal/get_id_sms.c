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

static int *mx_id_msgs(int *arr, int chat_id) {
	int rc = 0;
    int i = 0;
    char zSql[]="SELECT * FROM messages";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if ((sqlite3_column_int(stmt, 7) == chat_id) && sqlite3_column_int(stmt, 5) == 0){
                arr[i] = sqlite3_column_int(stmt, 0);
                i++;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while (rc == SQLITE_SCHEMA); {}
    return arr;
}


int *get_msgs_ids(int chat_id, int count_sms) {
    int *arr = malloc(sizeof(int) * (count_sms + 1));

    arr[count_sms] = -1;

    startDB();
    arr = mx_id_msgs(arr, chat_id);
    endDB();

    return arr;
}
