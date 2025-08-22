#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

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

    printf("开始在设备上抓包: %s\n", devices);

    char buffer[128];

    if (DEBUG_LOG) {
        if (mkdir("./logs", 0755) != 0 && errno != EEXIST) {
            perror("创建日志目录失败");
            exit(1);
        }

        time_t now = time(NULL);
        strftime(buffer, sizeof(buffer), "./logs/%Y-%m-%d-%H-%M-%S.log", localtime(&now));

        logger_init(buffer);
        
        printf("日志已启用: %s\n", buffer);
    } else {
        if (mkdir("./logs", 0755) != 0 && errno != EEXIST) {
            perror("创建日志目录失败");

            exit(1);
        }

        snprintf(buffer, sizeof(buffer), "./logs/default.log");
        logger_init(buffer);
    }

    start_capture(devices);

    logger_close();

    return 0;
}
