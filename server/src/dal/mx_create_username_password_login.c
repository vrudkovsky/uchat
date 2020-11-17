#include "server.h" 
#include <sqlite3.h>

sqlite3 *db;    // хэндл БД
// Структуры данных для базы данных
sqlite3_stmt* stmt; // строка запроса к БД

static void startDB() {
    char str[1000];
    // int lenstr=0;
    if( sqlite3_open("uchat.db", &db)) {
        printf(str, "Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
    }
}

static bool insertRecord(char *str_1, char *str_2, char *str_3) {

	char *string_1 = "INSERT INTO users (username, password, email, info, is_active, created_at, updated_at) VALUES ('";
    char *string_2 = str_3;
	char *string_3 = "', '";
	char *string_4 = str_2;
	char *string_5 = "', '";
	char *string_6 = str_1;
    char *string_7 = "', '";
    char *string_8 = "lorem ipsum dolor";
    char *string_9 = "', ";
    char *string_10 = "1";
    char *string_11 = ", '";
    char *string_12 = "14-10-2020";
    char *string_13 = "', '";
    char *string_14 = "14-10-2020";
	char *string_15 = "')";

    char *srt_buf = mx_strnew(1000);
    srt_buf = strcat(srt_buf, string_1);
    srt_buf = strcat(srt_buf, string_2);
    srt_buf = strcat(srt_buf, string_3);
    srt_buf = strcat(srt_buf, string_4);
    srt_buf = strcat(srt_buf, string_5);
    srt_buf = strcat(srt_buf, string_6);
    srt_buf = strcat(srt_buf, string_7);
    srt_buf = strcat(srt_buf, string_8);
    srt_buf = strcat(srt_buf, string_9);
    srt_buf = strcat(srt_buf, string_10);
    srt_buf = strcat(srt_buf, string_11);
    srt_buf = strcat(srt_buf, string_12);
    srt_buf = strcat(srt_buf, string_13);
    srt_buf = strcat(srt_buf, string_14);
    srt_buf = strcat(srt_buf, string_15);
	 printf("stroka %s\n", srt_buf);	

     printf("*** \tInsert into DB\t ***\n");
     sqlite3_prepare(db, srt_buf, -1, &stmt, 0);
     sqlite3_step(stmt);
     return 0;
}

static void endDB(){
    sqlite3_close(db);
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

bool mx_create_username_password_login(char *username, char *pass, char *email) { //затычка либы
	startDB();
	showDB();
	insertRecord(username, pass, email);
	showDB();
    endDB();
    return true;
}
