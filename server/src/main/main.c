#include "server.h"

int main(int argc, char **argv) {
    start_error(argc, argv);
    connection_establisher(mx_atoi(argv[1]));
    return 0;
}
