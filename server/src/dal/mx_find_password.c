#include "server.h" 

	sqlite3 *db;
	sqlite3_stmt* stmt; // строка запроса к БД

static void startDB() {
    sqlite3 *db;
    char str[1000];
    // int lenstr=0;
    if( sqlite3_open("uchat.db", &db)) {
        printf(str, "Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
    }
}

static void showDB() {
	int rc = 0;
    char zSql[]="SELECT * FROM users";
    printf("*** \tShow DB\t ***\n");
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

static bool find_password(char *pass, char *login) {
	int rc = 0;
    printf("\n%s                                 email", pass);
    char zSql[]="SELECT * FROM users";
    printf("*** \tShow DB\t ***\n");
    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {
                printf("%s\n", sqlite3_column_text(stmt,3));
                if (strcmp((const char*)sqlite3_column_text(stmt,1), login) == 0 ) {
                    if (strcmp((const char*)sqlite3_column_text(stmt,2), pass) == 0 ) {
                    printf("<--!!!!! Inside search function !!!!->");
                    return 1;
                    }
                }
            }
            rc = sqlite3_finalize(stmt);
        }
    while(rc == SQLITE_SCHEMA); {}
    return 0;
}

static void endDB(){
    sqlite3_close(db);
}

bool mx_find_password(char *pass, char *login) {
    printf("%s 11111111111111111111111111", pass);
	startDB();
	showDB();
	if(find_password(pass, login) != 0)
		return 1;
	showDB();
    endDB();
    return 0;
}
