#include "server.h"

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

void start_error(int argc, char **argv) {
    if (argc != 2)
        print_error_msg("usage: ./server [port]\n");
    port_checker(argv[1]);
}
