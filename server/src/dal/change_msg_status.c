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

static bool insertRecord(int message_id) {
    printf("%d\n", message_id);
    sqlite3_prepare_v2(db, "UPDATE messages SET msg_status = ? WHERE id = ?", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, 0);
    sqlite3_bind_int(stmt, 2, message_id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return true;
}

bool change_msg_status(int msg_id) {
    bool flag = false;

    startDB();
    if (insertRecord(msg_id))
        flag = true;
    endDB();

    return flag;
}
