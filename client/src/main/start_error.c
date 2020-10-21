#include "client.h"

void print_error_msg(char *msg) {
    mx_printerr(msg);
    exit(1);
}

void port_checker(char *port) {
    int port_len = mx_strlen(port);
    unsigned short port_num = 0;

    if (port_len < 4 || port_len > 5)
        print_error_msg("error: invalid port number\n");
    for (short i = 0; i < port_len; i++) 
        if (!mx_isdigit(port[i]))
            print_error_msg("error: invalid port number\n");
    port_num = mx_atoi(port);
    if (port_num < 1024 || port_num > 65535)
        print_error_msg("error: invalid port number\n");
}

void ip_format_checker(char *ip, int len) {
    short dots = 0;
    short digits;

    for (short i = 0; i < len; i++) {
        digits = 0;
        while (ip[i] != '.' && i < len) {
            digits++;
            i++;
        }
        dots++;
        if (digits < 1 || digits > 3)
            print_error_msg("error: invalid server IP address\n");
    }
    if (dots != 4)
       print_error_msg("error: invalid server IP address\n"); 
}

void ip_checker(char *ip) {
    int ip_len = mx_strlen(ip);

    if (ip_len < 7 || ip_len > 15)
        print_error_msg("error: invalid server IP address\n");
    for (short i = 0; i < ip_len; i++) 
        if (!mx_isdigit(ip[i]) && ip[i] != '.')
            print_error_msg("error: invalid server IP address\n");
    ip_format_checker(ip, ip_len);
}

void start_error(int argc, char **argv) {
    if (argc != 3)
        print_error_msg("usage: ./client [port] [server IP address]\n");
    port_checker(argv[1]);
    ip_checker(argv[2]);
}
