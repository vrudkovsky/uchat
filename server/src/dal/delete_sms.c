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

static bool insertRecord(int id_sms) {
    sqlite3_prepare_v2(db, "DELETE FROM messages WHERE id = ?", -1, &stmt, NULL);
    if (stmt != NULL) {
        sqlite3_bind_int(stmt, 1, id_sms);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        return true;
    }
    return false;
}

bool delete_sms(int id_sms) {

    bool flag = false;

    startDB();

    if(insertRecord(id_sms) == true)
        flag = true;

    endDB();
    return flag;
}
