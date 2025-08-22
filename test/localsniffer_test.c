#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>

#define DEBUG_LOG false

#ifndef DEFAULT_IFACE
#   ifdef __APPLE__
#       define DEFAULT_IFACE "en0"
#   else
#       define DEFAULT_IFACE "eth0"
#   endif
#endif

static FILE *logfile = NULL;

void logger_init(const char *filepath) {
    logfile = fopen(filepath, "a");
    if (!logfile) perror("日志文件打开失败");
}

void logger_close() {
    if (logfile) fclose(logfile);
}

void start_capture(const char *device) {
    printf("模拟抓包: %s\n", device);
}

const char* get_default_device(int argc, char *argv[]) {
    return (argc > 1 ? argv[1] : DEFAULT_IFACE);
}

int prepare_log_directory(void) {
    if (mkdir("./logs", 0755) != 0 && errno != EEXIST) {
        perror("创建日志目录失败");
        return -1;
    }
    return 0;
}

void prepare_log_file(char *buffer, size_t size, bool debug) {
    time_t now = time(NULL);
    if (debug) {
        strftime(buffer, size, "./logs/%Y-%m-%d-%H-%M-%S.log", localtime(&now));
    } else {
        snprintf(buffer, size, "./logs/default.log");
    }
    logger_init(buffer);
}

int test_default_device() {
    char *argv1[] = {"sniff"};
    if (strcmp(get_default_device(1, argv1), DEFAULT_IFACE) != 0) return 1;
    char *argv2[] = {"sniff", "wlan0"};
    if (strcmp(get_default_device(2, argv2), "wlan0") != 0) return 1;
    return 0;
}

int test_prepare_log_directory() {
    if (prepare_log_directory() != 0) return 1;
    if (prepare_log_directory() != 0) return 1;
    return 0;
}

int test_prepare_log_file() {
    char buffer[128];
    prepare_log_file(buffer, sizeof(buffer), true);
    FILE *f = fopen(buffer, "r");
    if (!f) return 1;
    fclose(f);
    prepare_log_file(buffer, sizeof(buffer), false);
    f = fopen(buffer, "r");
    if (!f) return 1;
    fclose(f);
    return 0;
}

int main() {
    int fail = 0;
    printf("测试默认设备选择...");
    if (test_default_device() == 0) printf("通过\n"); else {printf("失败\n"); fail++;}
    printf("测试日志目录创建...");
    if (test_prepare_log_directory() == 0) printf("通过\n"); else {printf("失败\n"); fail++;}
    printf("测试日志文件生成...");
    if (test_prepare_log_file() == 0) printf("通过\n"); else {printf("失败\n"); fail++;}
    printf("测试完成: %d 失败\n", fail);
    return fail;
}
