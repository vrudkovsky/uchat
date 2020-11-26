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

static bool find_user_in_contacts(int id_who, int id_whom) {
    int rc = 0;
    char zSql[]="SELECT * FROM user_contacts";
    bool flag = false;

    if (id_who != id_whom) {
        do {
            sqlite3_prepare(db, zSql, -1, &stmt_1, 0);
            while(SQLITE_ROW == sqlite3_step(stmt_1)) {
                if ((sqlite3_column_int(stmt_1,0) == id_who) && (sqlite3_column_int(stmt_1,1) == id_whom)) {
                    flag = true;
                    break;
                }
            }
            rc = sqlite3_finalize(stmt_1);
        }
        while(rc == SQLITE_SCHEMA); {}
    }
    return flag;
}

static int count_chats(int user_id) {
	int rc = 0;
    int count = 0;
    char zSql[] = "SELECT * FROM conversations";
    int creator = 0;
    int acceptor = 0;

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            creator = sqlite3_column_int(stmt, 1);
            acceptor = sqlite3_column_int(stmt, 2);
            if (creator ==  user_id) {
                if (find_user_in_contacts(user_id, acceptor)) {
                    count++;
                }
            }
            else if (acceptor ==  user_id) {
                if (find_user_in_contacts(user_id, creator)) {
                    count++;
                }
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while (rc == SQLITE_SCHEMA); {}
    return count;
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
    while (rc == SQLITE_SCHEMA); {}
    return id;
}

int mx_count_chats(char *username) {
    int count;
    int user_id;

	startDB();
    user_id = find_who_id(username);
    count = count_chats(user_id);
    endDB();

	return count;
}
