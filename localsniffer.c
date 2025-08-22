#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "./include/capture.h"
#include "./include/logger.h"

#define DEBUG_LOG false

#ifndef DEFAULT_IFACE
#   ifdef __APPLE__
#       define DEFAULT_IFACE "en0"
#   else
#       define DEFAULT_IFACE "eth0"
#   endif
#endif

int main(int argc, char *argv[]) {
    const char *devices = (argc > 1 ? argv[1] : DEFAULT_IFACE);

    printf("Starting capture on device: %s\n", devices);

    char buffer[128];

    if (DEBUG_LOG) {

        if (mkdir("./logs", 0755) != 0) {
            //
        }

        time_t now = time(NULL);
        strftime(buffer, sizeof(buffer), "./logs/%Y-%m-%d-%H-%M-%S.log", localtime(&now));

        logger_init(buffer);
        printf("Logging enabled: %s\n", buffer);
    } else {
        snprintf(buffer, sizeof(buffer), "./logs/default.log");
        mkdir("./logs", 0755); // 确保目录存在
        logger_init(buffer);
    }

    start_capture(devices);

    logger_close();

    return 0;
}
