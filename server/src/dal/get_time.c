#include "server.h" 
#include <sqlite3.h>

    sqlite3 *db;
    sqlite3_stmt* stmt; // строка запроса к БД


static void startDB() {
    char str[1000];
    // int lenstr=0;
    if( sqlite3_open("uchat.db", &db)) {
        printf(str, "Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
    }
}

static void endDB(){
    sqlite3_close(db);
}

static const char *find_whom_id(char *whom) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM users";

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {


                //printf("%s\n", sqlite3_column_text(stmt,1));

                if (strcmp((const char*)sqlite3_column_text(stmt,1), whom) == 0 ) {
                    //printf("нашел нужного юзера\n");
                    //printf("%s\n", sqlite3_column_text(stmt,3));
                    const char *id = mx_strnew(255);
                    id = (const char*)sqlite3_column_text(stmt,0);
                    return id;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    char *err = "-1";
    return err;
}


static int contact_id_message(const char *id_who, const char *id_whom, int i) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM messages";
    int count = 0;
    int krugi = -1;

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {


                //printf("%s\n", sqlite3_column_text(stmt,0));

                if ((strcmp((const char*)sqlite3_column_text(stmt,1), id_who) == 0 ) && (strcmp((const char*)sqlite3_column_text(stmt,2), id_whom) == 0 ))
                    krugi++;

                if ((strcmp((const char*)sqlite3_column_text(stmt,1), id_whom) == 0 ) && (strcmp((const char*)sqlite3_column_text(stmt,2), id_who) == 0 ))
                    krugi++;

                    if(krugi == i) {
                        int res;
                        res = sqlite3_column_int(stmt,6);
                        rc = sqlite3_finalize(stmt);
                        return res;
                    }
            }
                rc = sqlite3_finalize(stmt);
                }
    while(rc == SQLITE_SCHEMA); {}
    return -1;
}


int *mx_get_time(char *who, char *whom, int count_sms) {
    startDB();

    const char *friends_1 = find_whom_id(who);   //получили айди  чувака 1
    const char *friends_2 = find_whom_id(whom); //получили айди  чувака 2
    int *arr = malloc((sizeof(int)) * count_sms);
    int i = 0;

    while (i < count_sms) {
        arr[i] = contact_id_message(friends_1, friends_2, i);
        //printf("%d\n", arr[i]);
        i++;
    }
    endDB();
    return arr;
}
