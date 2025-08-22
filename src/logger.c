#include <stdio.h>
#include <string.h>

#include "../include/logger.h"
#include "../include/utilities.h"

static FILE *logfile = NULL;

#define COLOR_HTTP   "\x1b[32m"
#define COLOR_HTTPS  "\x1b[34m"
#define COLOR_RESET  "\x1b[0m"

void logger_init(const char *filepath) {
    logfile = fopen(filepath, "a");
    if (!logfile) perror("日志文件打开失败");
}

void logger_log(const RequestEvent *ev) {
    char timestr[0x40];

    format_time(ev->timestamp, timestr, sizeof(timestr));

    if (strcmp(ev->protocol, "HTTP") == 0x0) {
        fprintf(stdout, "%s %s %s请求%s http://%s%s\n", timestr, ev -> src_ip, COLOR_HTTP, COLOR_RESET, ev -> host, ev -> path);

        if (logfile) fprintf(logfile, "%s %-15s 请求 http://%s%s\n", timestr, ev -> src_ip, ev -> host, ev -> path);
    } else {
        fprintf(stdout, "%s %s %s请求%s https://%s\n", timestr, ev -> src_ip, COLOR_HTTPS, COLOR_RESET, ev -> host);

        if (logfile) fprintf(logfile, "%s %-15s 请求 https://%s\n", timestr, ev -> src_ip, ev -> host);
    }

    fflush(stdout);
    
    if (logfile) fflush(logfile);
}

void logger_close() {
    if (logfile) {
        fclose(logfile);
        logfile = NULL;
    }
}
