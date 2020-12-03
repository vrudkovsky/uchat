#include "server.h" 
#include <sqlite3.h>

sqlite3 *db; 
sqlite3_stmt* stmt;

static void startDB() {
    if (sqlite3_open("uchat.db", &db)) {
        printf("Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
    }
}

static void endDB(){
    sqlite3_close(db);
}

static int find_last_msg_id(int chat_id) {
    int rc = 0;
    int id = -1;
    char zSql[]= "SELECT * FROM messages";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (sqlite3_column_int(stmt, 7) == chat_id) {
                id = sqlite3_column_int(stmt, 0);
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while(rc == SQLITE_SCHEMA); {}
    return id;
}

static bool insertRecord(int sender, int recipient, char *text, int created_at, int msg_status, int chat_id) {
    sqlite3_prepare_v2(db, "INSERT INTO messages (sender_id, recipient_id, msg_text, updated_at, msg_status, created_at, chat_id) VALUES (?, ?, ?, ?, ?, ?, ?)", -1, &stmt, NULL);
    if (stmt != NULL) {
        sqlite3_bind_int(stmt, 1, sender);
        sqlite3_bind_int(stmt, 2, recipient);
        sqlite3_bind_text(stmt, 3, text, -1, 0);
        sqlite3_bind_text(stmt, 4, "NULL", -1, 0);
        sqlite3_bind_int(stmt, 5, msg_status);
        sqlite3_bind_int(stmt, 6, created_at); 
        sqlite3_bind_int(stmt, 7, chat_id); 
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        return true;
    }
    return false;
}

static bool check_relations(int who, int to_whom) {
    bool flag = false;
    int rc = 0;
    int id = -1;
    char zSql[]= "SELECT * FROM user_contacts";

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if ((sqlite3_column_int(stmt, 0) == who) && (sqlite3_column_int(stmt, 1) == to_whom)) {
                flag = true;
                break;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while(rc == SQLITE_SCHEMA); {}
    return flag;
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

int insert_new_msg(char *who, char *whom, char *text, int created_at, int chat_id) {
    startDB();
    int msg_id = -1;
    int msg_status = 1;
    int sender = find_who_id(who);
    int recipient = find_who_id(whom);
    if (!check_relations(recipient, sender))
        msg_status = 2;

    if (insertRecord(sender, recipient, text, created_at, msg_status, chat_id))
        msg_id = find_last_msg_id(chat_id);
    return msg_id;
}
