#include "client.h"

int main(int argc, char **argv) {
    short sockfd;

    start_error(argc, argv);
    connection_establisher(mx_atoi(argv[1]), argv[2]);

    main_data.app_status = 2;
    main_data.username = "bob";
    while (main_data.app_status != 3)
        switch (main_data.app_status) {
            case 1: log_reg_window(); break;
            case 2: chat_window_main(); main_data.app_status = 3; break;
        }
    return 0;
}
