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
                    rc = sqlite3_finalize(stmt);
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

static const char *username_1(char *id_chat) { //затычка либы
	int rc = 0;
    char zSql[]="SELECT * FROM conversations";
    //printf("*** \tShow DB\t ***\n");
    do
        {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);

            while(SQLITE_ROW == sqlite3_step(stmt)) {
                if (strcmp((const char*)sqlite3_column_text(stmt,0), id_chat) == 0 ) {
                    rc = sqlite3_finalize(stmt);
                    return (const char*)sqlite3_column_text(stmt,1);
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    return "-1";
}


static const char *username_2(char *id_chat) { //затычка либы
    int rc = 0;
    char zSql[]="SELECT * FROM conversations";
    //printf("*** \tShow DB\t ***\n");
    do
        {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);

            while(SQLITE_ROW == sqlite3_step(stmt)) {
                if (strcmp((const char*)sqlite3_column_text(stmt,0), id_chat) == 0 ) {
                    rc = sqlite3_finalize(stmt);
                    return (const char*)sqlite3_column_text(stmt,2);
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    return "-1";
}

static int count_sms(const char *username_1, const char *username_2) { //затычка либы
	int rc = 0;
    int count = 0;
    char zSql[]="SELECT * FROM messages";
    //printf("*** \tShow DB\t ***\n");
    do
        {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);

            while(SQLITE_ROW == sqlite3_step(stmt)) {
                if ((strcmp((const char*)sqlite3_column_text(stmt,1), username_1) == 0 ) &&  strcmp((const char*)sqlite3_column_text(stmt,2), username_2) == 0) {
 					count++;
                }
                if ((strcmp((const char*)sqlite3_column_text(stmt,1), username_2) == 0 ) &&  strcmp((const char*)sqlite3_column_text(stmt,2), username_1) == 0) {
 					count++;
                }

            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    return count;
}


int mx_count_sms(char *id_chat) {
	startDB();
	int arr = 0;
	//showDB();

    const char *username_11 = mx_strnew(255);
    const char *username_22 = mx_strnew(255);
    username_11 = username_1(id_chat);
    username_22 = username_2(id_chat);

//printf("*************************************username_11 %s\n", username_22);
        arr = count_sms(username_11, username_22);
        //printf("count chaty usera%d\n", r);
        endDB();
		return arr;
    
	//showDB();
    //endDB();
    //return arr;
}

