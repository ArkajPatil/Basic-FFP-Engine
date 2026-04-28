#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

// global log file pointer
extern FILE *gpFile ;

// functions
void writeLog(const char *format, ...);
void cleanupLogger(void);

#endif