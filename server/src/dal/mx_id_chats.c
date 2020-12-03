
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


static const char *find_username_id(char *username) { //затычка либы
    int rc = 0;
    //printf("\n%s                                 username", username);
    char zSql[]="SELECT * FROM users";
    //printf("*** \tShow DB\t ***\n");
    do
        {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);

            while(SQLITE_ROW == sqlite3_step(stmt)) {
                //printf("%s\n", sqlite3_column_text(stmt,1));

                if (strcmp((const char*)sqlite3_column_text(stmt,1), username) == 0 ) {
                    //printf("<--!!!!! Inside search function !!!!->");
                    rc = sqlite3_finalize(stmt);
                    return (const char*)sqlite3_column_text(stmt,0);
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    return "-1";
}


static char **mx_id_chaty_user(const char *num_id_who) { //затычка либы
	int rc = 0;
    int count = 0;
    char zSql[]="SELECT * FROM conversations";
    char **arr_1 = NULL;
    arr_1 = malloc(sizeof(char *) * (255));
    int i = 0;
    //printf("*** \tShow DB\t ***\n");
    do
        {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);

            while(SQLITE_ROW == sqlite3_step(stmt)) {
                if ((strcmp((const char*)sqlite3_column_text(stmt,1), num_id_who) == 0 ) || (strcmp((const char*)sqlite3_column_text(stmt,2), num_id_who) == 0 )){
                    arr_1[i] = mx_strnew(255);
                    arr_1[i] = mx_strcpy(arr_1[i], (char*)sqlite3_column_text(stmt,0));
                    arr_1[i+1] = NULL;
                    i++;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    return arr_1;
}


char **mx_id_chats(char *who) {
    //printf("who %s\n", who);
    startDB();
    char **arr = NULL;
    arr = malloc(sizeof(char *) * (255));
    const char *num_id_who = find_username_id(who); //вернули айди пользователя
	

    arr = mx_id_chaty_user(num_id_who);
    endDB();
    return arr;
}
