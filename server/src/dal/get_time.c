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

static int mx_msgs_time(int msg_id) {
	int rc = 0;
    int i = 0;
    char zSql[]="SELECT * FROM messages";
    int arr = 0;

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (sqlite3_column_int(stmt, 0) == msg_id) {
                arr = sqlite3_column_int(stmt, 6);
                i++;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while (rc == SQLITE_SCHEMA); {}
    return arr;
}


int *mx_get_time(int *msg_id, int count_sms) {
    int *arr = malloc(sizeof(int) * (count_sms + 1));

    arr[count_sms] = -1;

    startDB();
    for (int i = 0; i < count_sms; i++) {
        arr[i] = mx_msgs_time(msg_id[i]);
    }
    endDB();

    return arr;
}
