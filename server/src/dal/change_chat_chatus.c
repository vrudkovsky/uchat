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

static bool insertRecord(int chat_id) {
    sqlite3_prepare_v2(db, "UPDATE conversations SET status = ? WHERE id = ?", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, 0);
    sqlite3_bind_int(stmt, 2, chat_id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return true;

}

bool change_chat_status(int chat_id) {
    bool flag = false;

    startDB();
    if (insertRecord(chat_id))
        flag = true;
    endDB();

    return flag;
}
