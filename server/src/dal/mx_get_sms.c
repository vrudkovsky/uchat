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

static char *mx_msg_text(char *arr, int chat_id) {
	int rc = 0;
    int i = 0;
    char zSql[]="SELECT * FROM messages";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (sqlite3_column_int(stmt, 0) == chat_id)  {
                arr = mx_strdup((const char*)sqlite3_column_text(stmt, 3));
                i++;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while (rc == SQLITE_SCHEMA); {}
    return arr;
}


char **mx_get_msg_text(int *msg_id, int count_sms) {
    char **arr = malloc(sizeof(char*) * (count_sms + 1));

    arr[count_sms] = NULL;

    startDB();
    for (int i = 0; i < count_sms; i++)
        arr[i] = mx_msg_text(arr[i], msg_id[i]);
    endDB();

    return arr;
}
