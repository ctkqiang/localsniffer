#include <time.h>
#include <stdio.h>

#include "../include/utilities.h"

void format_time(time_t ts, char *buf, size_t len) {
    struct tm *tm_info = localtime(&ts);
    strftime(buf, len, "%Y-%m-%d %H:%M:%S", tm_info);
}
