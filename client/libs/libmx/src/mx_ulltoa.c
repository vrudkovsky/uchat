#include "libmx.h"

static int mx_ulllen(unsigned long long num) {
    int len = 1;

    while (num /= 10)
        len++;
    return len;
}

char *mx_ulltoa(unsigned long long number) {
    int num_len = mx_ulllen(number);
    char *result = mx_strnew(num_len);

    if (number == 0)
            result = mx_strcpy(result, "0");
    else {
        result[num_len] = '\0';
        while (number) {
            result[--num_len] = (char) ((number % 10) + 48);
            number /= 10;
        }
    }
    return result;
}
