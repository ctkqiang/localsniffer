#pragma once

#ifndef PARSER_H
#define PARSER_H

#include <time.h>

typedef struct  {
    char src_ip[0x40];
    char protocol[0x8];
    char host[0x100];
    char path[0x200];

    time_t timestamp;
} RequestEvent;

void parse_packet(const unsigned char *packet, int len);

#endif
