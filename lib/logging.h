#ifndef __EXTCLIB_LOGGING_H
#define __EXTCLIB_LOGGING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

typedef enum LogType {
  INFO,
  ERR,
  DEBUG
} LogFileT;

FILE* initLogger(char *filename);

void logMessage(FILE* logFile, char *filename, LogFileT logType, const char *format, ...);

void closeLogger(FILE* logFile);

extern FILE* logFile;

#endif /* __EXTCLIB_NET_H */
