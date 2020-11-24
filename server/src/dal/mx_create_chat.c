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

static const char *id_message(const char *id_who, const char *id_whom) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM conversations";
    int count = 0;
    int krugi = -1;

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {


                //printf("%s\n", sqlite3_column_text(stmt,0));

                if ((strcmp((const char*)sqlite3_column_text(stmt,1), id_who) == 0 ) && (strcmp((const char*)sqlite3_column_text(stmt,2), id_whom) == 0 )) {
                        const char *res = mx_strnew(255);
                        res = (const char*)sqlite3_column_text(stmt,0);
                        rc = sqlite3_finalize(stmt);
                        return res;
                }
                if ((strcmp((const char*)sqlite3_column_text(stmt,1), id_whom) == 0 ) && (strcmp((const char*)sqlite3_column_text(stmt,2), id_who) == 0 )) {
                        const char *res = mx_strnew(255);
                        res = (const char*)sqlite3_column_text(stmt,0);
                        rc = sqlite3_finalize(stmt);
                        return res;
                }
            }
                rc = sqlite3_finalize(stmt);
                }
    while(rc == SQLITE_SCHEMA); {}
    return "-2";
}

static void endDB(){
    sqlite3_close(db);
}

static void showDB() {
    int rc = 0;
    char zSql[]="SELECT * FROM messages";
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
    rc = sqlite3_finalize(stmt);
}

static char *id(const char *username) { //находит айди whom
    int rc = 0;
    char zSql[]="SELECT * FROM users";
    int count = 0;
    int krugi = -1;

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {


                //printf("%s\n", sqlite3_column_text(stmt,0));

                if (strcmp((const char*)sqlite3_column_text(stmt,1), username) == 0) {
                        char *res = mx_strnew(255);
                        res = (char*)sqlite3_column_text(stmt,0);
                        rc = sqlite3_finalize(stmt);
                        return res;
                }
            }
                rc = sqlite3_finalize(stmt);
                }
    while(rc == SQLITE_SCHEMA); {}
    return "-1";
}


static int last_id(void) { //находит айди whom
    int rc = 0;
    char *zSql = mx_strnew(255);
    zSql = "SELECT * FROM conversations";
    int count = 0;
    int krugi = -1;

    do {
            sqlite3_prepare(db, zSql, -1, &stmt, 0);
            while(SQLITE_ROW == sqlite3_step(stmt)) {
                if ((const char*)sqlite3_column_text(stmt,0)) {
                count++;
                }
            }
                rc = sqlite3_finalize(stmt);
                }
    while(rc == SQLITE_SCHEMA); {}
    return count;

}


    static void insertRecord(char *id, char *username1, char *username2) {
            //static void insertRecord(void) {
    //int i = mx_atoi(id);

    char *string_1 = "INSERT INTO conversations (id, user1_id, user2_id) VALUES (";
    char *string_2 = id;
    char *string_3 = ", '";
    char *string_4 = username1;
    char *string_5 = "', '";
    char *string_6 = username2;
    char *string_7 = "')";

    char *srt_buf = mx_strnew(1000);
    srt_buf = strcat(srt_buf, string_1);
    srt_buf = strcat(srt_buf, string_2);
    srt_buf = strcat(srt_buf, string_3);
    srt_buf = strcat(srt_buf, string_4);
    srt_buf = strcat(srt_buf, string_5);
    srt_buf = strcat(srt_buf, string_6);
    srt_buf = strcat(srt_buf, string_7);
     printf("stroka %s\n", srt_buf);    

     printf("*** \tInsert into DB\t ***\n");
     sqlite3_prepare(db, srt_buf, -1, &stmt, 0);
     sqlite3_step(stmt);
     int rc = sqlite3_finalize(stmt);
}



int mx_create_chat(const char *username_1, const char *username_2) { //затычка либы
    startDB();
    //showDB();
    char *user_1_id = mx_strnew(255);
    char *user_2_id = mx_strnew(255);
    char *id_chat_str = mx_strnew(255);
    user_1_id = id(username_1);
    user_2_id = id(username_2);
    int id_chat = last_id(); //последний номер строки conversations
    //if (id_chat == 0)
        id_chat++;
    id_chat_str = mx_itoa(id_chat);
    // printf("id_chat%s\n", id_chat_str);
    // printf("user_1_id%s\n", user_1_id);
    // printf("user_2_id%s\n", user_2_id);
    insertRecord(id_chat_str, user_1_id, user_2_id);
    const char *res = id_message(user_1_id, user_2_id);
    int ress = mx_atoi(res);
    if (ress <= 0) 
        ress = 0;
    //printf("%d\n", id_chat);
    //insertRecord();
    //showDB();
    endDB();
    return ress;

}
