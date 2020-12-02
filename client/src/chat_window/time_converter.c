#include "client.h"

char *time_converter(int seconds, short mode) {
    
    //** timezone and bias    
    //tzset();

    //** received time ts
    //const long s = (long)seconds + timezone;
    const long s = (long)seconds;
    const int day = 86400;
    struct tm ts;
    ts = *localtime(&s);
    char *buf = malloc(sizeof(long)); 

    const char *st = ctime(&s);
    char **arr = mx_strsplit(st, ' ');
    char *bufDay = malloc(sizeof(int));
    char *bufMon = malloc(sizeof(int)); 
    char *bufTime = malloc(sizeof(int)); 

    //** rawtime ptm
    time_t rawtime = time(NULL);
    struct tm ptm;
    ptm = *localtime(&rawtime);


    // checking yesterday 
    int yesterday;
    yesterday = (rawtime / day) - (s / day);

    // time converter output
    switch (mode) {

        case 0:
            if((ptm.tm_year == ts.tm_year) 
                && (ptm.tm_mon == ts.tm_mon) 
                && (ptm.tm_mday == ts.tm_mday)) {
                strftime(buf, sizeof(buf)*6, "Today, %H:%M", &ts);
                return buf;
            } 
            else if(yesterday == 1) {
                strftime(buf, sizeof(buf)*6, "Yesterday, %H:%M", &ts);
                return buf;
            } 
            else {
                for (int i = 0; i < 3; i++) {
                    bufDay[i] = arr[2][i];
                }
                strcat(buf, bufDay);
                strcat(buf, " ");

                for (int i = 0; i < 4; i++) {
                    bufMon[i] = arr[1][i];
                }
                strcat(buf, bufMon);

                return buf;
            }
            return buf;
            break;
        
        case 1:
            if((ptm.tm_year == ts.tm_year) 
                && (ptm.tm_mon == ts.tm_mon) 
                && (ptm.tm_mday == ts.tm_mday)) {
                strftime(buf, sizeof(buf)*6, "Today, %H:%M", &ts);
                return buf;
            } 
            else if(yesterday == 1) {
                strftime(buf, sizeof(buf)*6, "Yesterday, %H:%M", &ts);
                return buf;
            } 
            else {
                for (int i = 0; i < 3; i++) {
                    bufDay[i] = arr[2][i];
                }
                strcat(buf, bufDay);
                strcat(buf, " ");

                for (int i = 0; i < 4; i++) {
                    bufMon[i] = arr[1][i];
                }
                strcat(buf, bufMon);
                strcat(buf, ", ");

                for (int i = 0; i < 5; i++) {
                    bufTime[i] = arr[3][i];
                }
                strcat(buf, bufTime);

                return buf;
            }
            return buf;
            break;
        
        default:
            break;
    }
    return 0;
}

