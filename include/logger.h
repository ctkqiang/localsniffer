#pragma once 

#ifndef LOGGER_H
#define LOGGER_H

#include "parser.h"

void logger_init(const char* FILE_PATH);
void logger_log(const RequestEvent *EVENT);
void logger_close();

#endif