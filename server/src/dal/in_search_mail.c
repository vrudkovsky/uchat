//Получает имя пользователя и возвращает его мейл в виде строки работает
//clang -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic \
//        -Wno-unused-command-line-argument -Wno-unused-variable \
//        -Wno-unused-function -Wno-unused-parameter -g -lsqlite3 in_search_mail.c
 
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


static void showDB() {
    int rc = 0;
    char zSql[]="SELECT * FROM users";
    //printf("*** \tShow DB\t ***\n");
    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {
                printf("%d\t%s\t%s\t%s\t%s\t%d\t%s\t%s\n",
                        sqlite3_column_int(stmt,0),
                        sqlite3_column_text(stmt,1),
                        sqlite3_column_text(stmt,2),
                        sqlite3_column_text(stmt,3),
                        sqlite3_column_text(stmt,4),
                        sqlite3_column_int(stmt,5),
                        sqlite3_column_text(stmt,6),
                        sqlite3_column_text(stmt,7));
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA);
}

static const char *mx_in_search_mail(char *email) { //затычка либы
    int rc = 0;
    //printf("\n%s                                 email", email);
    char zSql[]="SELECT * FROM users";
    //printf("*** \tShow DB\t ***\n");
    do
        {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);

            while(SQLITE_ROW == sqlite3_step(stmt)) {


                //printf("%s\n", sqlite3_column_text(stmt,1));

                if ( strcmp((const char*)sqlite3_column_text(stmt,1), email) == 0 ) {
                    printf("нашел нужного юзера\n");
                    //printf("%s\n", sqlite3_column_text(stmt,3));
                    const char *srt = (const char*)sqlite3_column_text(stmt,3);
                    //printf("%s\n", srt);
                    return srt;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    return 0;
}

const char *in_search_mail(char *username) {
    startDB();
    showDB();
    if(mx_in_search_mail(username) != 0)
        return (mx_in_search_mail(username));
    return 0;
}

