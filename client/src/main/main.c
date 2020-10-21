#include "client.h"

int main(int argc, char **argv) {
    short sockfd;

    start_error(argc, argv);
    connection_establisher(mx_atoi(argv[1]), argv[2]);
    
    log_reg_window();
    
    return 0;
}
