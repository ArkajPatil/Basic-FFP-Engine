#ifndef LOGGER_H
#define LOGGER_H

#include<stdio.h>
// global file pointer
extern FILE *gpFile;

// functions declarations
void writeLog(const char *format, ...);

#endif