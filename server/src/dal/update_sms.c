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

static bool insertRecord(int id_sms, char *text_sms) {

    sqlite3_prepare_v2(db, "UPDATE messages SET msg_text = ? WHERE id = ?", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, text_sms, -1, 0);
    sqlite3_bind_int(stmt, 2, id_sms);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return true;

}

bool update_sms(int id_sms, char *text_sms) {

    bool flag = false;

    startDB();
    printf("startdb");
    if(insertRecord(id_sms, text_sms) == true)
        flag = true;

    endDB();
    return flag;
}
