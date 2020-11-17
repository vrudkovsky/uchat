#include "server.h" 
#include <sqlite3.h>

	sqlite3 *db;
	sqlite3_stmt* stmt; // строка запроса к БД


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

                    return (const char*)sqlite3_column_text(stmt,0);
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    return 0;
}



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


// static void showDB() {
//     int rc = 0;
//     char zSql[]="SELECT * FROM conversations";
//     //printf("*** \tShow DB\t ***\n");
//     do {
//             sqlite3_prepare(db, zSql, -1, &stmt, 0);
//             while(SQLITE_ROW == sqlite3_step(stmt)) {
//                 printf("%d\t%s\t%s\t%s\t%s\t%d\t%s\t%s\n",
//                         sqlite3_column_int(stmt,0),
//                         sqlite3_column_text(stmt,1),
//                         sqlite3_column_text(stmt,2),
//                         sqlite3_column_text(stmt,3),
//                         sqlite3_column_text(stmt,4),
//                         sqlite3_column_int(stmt,5),
//                         sqlite3_column_text(stmt,6),
//                         sqlite3_column_text(stmt,7));
//             }
//             rc = sqlite3_finalize(stmt);
//         }
//     while(rc == SQLITE_SCHEMA);
// }

static int mx_count_chaty_user(const char *id_username) { //затычка либы
	int rc = 0;
    int count = 0;
    //printf("\n%s                                 id_username\n", id_username);
    char zSql[]="SELECT * FROM conversations";
    //printf("*** \tShow DB\t ***\n");
    do
        {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);

            while(SQLITE_ROW == sqlite3_step(stmt)) {
                if (((strcmp((const char*)sqlite3_column_text(stmt,1), id_username) == 0 ) && (id_username != NULL)) ||(strcmp((const char*)sqlite3_column_text(stmt,2), id_username) == 0 )) {
                   count++;
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    return count;
}

int mx_count_chaty(char *username) {
	startDB();
    int r = 0;
    //printf("++++++%s\n", username);
	//showDB();
    const char *num = find_username_id(username);
	
        r = mx_count_chaty_user(num);
        //printf("count chaty usera***********%d\n", r);

	//showDB();
    //endDB();
    return r;
}
