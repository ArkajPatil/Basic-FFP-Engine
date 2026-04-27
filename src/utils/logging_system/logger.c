#include "logger.h"
#include <stdarg.h> // for writeLog function
#include <time.h>   // for writeLog function

FILE *gpFile = NULL;

void writeLog(const char *format, ...) // use this function only after log file has been created
{
    if (gpFile == NULL)
        return;

    // for timming
    time_t rawTime;                          // store current time in seconds
    struct tm *timeInfo;                     // structure to store readeable time
    char timeBuffer[64];                     // buffer to store formatted time string
    time(&rawTime);                          // Get current system time
    timeInfo = localtime(&rawTime);          // convert raw time to local time format
    strftime(timeBuffer, sizeof(timeBuffer), // format the time into a readadable string and store it in timeBuffer
             "%Y-%m-%d %H:%M:%S", timeInfo); // define the format as Year-Month-Day Hour:Minute:Second

    fprintf(gpFile, "[%s] ", timeBuffer); // print timestamp first

    // for format string input as parameter
    va_list args;           // Declares a special variable used to access the extra arguments.
    va_start(args, format); // Initializes args to start reading arguments after format.

    vfprintf(gpFile, format, args); // Writes the formatted output (using the extra arguments) into the file.
    fprintf(gpFile, "\n");

    va_end(args); // Cleans up the variable argument handling.

    fflush(gpFile); // Forces buffered data to be written immediately to the file.
}


