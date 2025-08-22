#include <stdio.h>
#include <string.h>

#include "../include/logger.h"
#include "../include/utilities.h"

static FILE *logfile = NULL;

void logger_init(const char *filepath) {
    logfile = fopen(filepath, "a");
    if (!logfile) perror("logfile");
}

void logger_log(const RequestEvent *ev) {
    char timestr[0x40];

    format_time(ev -> timestamp, timestr, sizeof(timestr));

    if (strcmp(ev -> protocol, "HTTP") == 0x0) {
        fprintf(stdout, "%s %s REQUESTED http://%s%s\n", timestr, ev -> src_ip, ev -> host, ev -> path);
        
        if (logfile) fprintf(logfile, "%s %s REQUESTED http://%s%s\n", timestr, ev -> src_ip, ev -> host, ev -> path);
    } else {
        fprintf(stdout, "%s %s REQUESTED https://%s\n", timestr, ev -> src_ip, ev -> host);
        
        if (logfile) fprintf(logfile, "%s %s REQUESTED https://%s\n", timestr, ev -> src_ip, ev -> host);
    }
}

void logger_close() {
    if (logfile) fclose(logfile);
}
