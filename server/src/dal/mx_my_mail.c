#include "server.h" 
#include <sqlite3.h>

    sqlite3 *db;
    sqlite3_stmt* stmt;

static void startDB() {
    if( sqlite3_open("uchat.db", &db))
        printf("Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
}

static void endDB(){
    sqlite3_close(db);
}

static char *friend_email(int id_who, char *email) {
    int rc = 0;
    char zSql[]="SELECT * FROM users";
    int count = 0;

    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (sqlite3_column_int(stmt,0) == id_who) {
                email = mx_strdup((const char*)sqlite3_column_text(stmt,3));
                break;
            }
        }
        rc = sqlite3_finalize(stmt);
        }
    while (rc == SQLITE_SCHEMA); {}
    return email;
}

static int friend_contact_id(int id_who, int i, int count_friends) {
    int rc = 0;
    char zSql[]="SELECT * FROM user_contacts";
    int res = -1;
    int cycles = 1;


    do {
        sqlite3_prepare(db, zSql, -1, &stmt, 0);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            if (sqlite3_column_int(stmt,0) == id_who) {
                if (cycles == i) {
                    res = sqlite3_column_int(stmt,1);
                    break;
                }
                cycles++;
            }
        }
        rc = sqlite3_finalize(stmt);
    }
    while (rc == SQLITE_SCHEMA); {}
    return res;
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

char **mx_my_mail(char *who) {
    int id_who;
    int count_contacts;
    int contact_id;
    char *contact_email = NULL;
    char **result = NULL;

    count_contacts = count_friends(who);
    result = malloc(sizeof(char*) * (count_contacts + 1));
    result[count_contacts] = NULL;

    startDB();
    id_who = find_who_id(who);
    
    for (int i = 1; i <= count_contacts; i++) {
        contact_id = friend_contact_id(id_who, i, count_contacts);
        result[i - 1] = friend_email(contact_id, result[i - 1]);
    }

    endDB();
    return result;
}
