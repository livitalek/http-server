#include "logging.h"

FILE* logFile = NULL;

FILE* initLogger(char *filename) {

    FILE* logFile = fopen(filename, "a");

    if (logFile == NULL) {
        fprintf(stderr, "Не удалось открыть файл логирования: %s\n", filename);
        exit(1);
    }

    return logFile;

}

void logMessage(FILE* logFile, char *filename, LogFileT logType, const char *format, ...) {

    logFile = initLogger(filename);
    va_list args;
    va_start(args, format);
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    if (logType == INFO) {
        fprintf(logFile, "[%02d-%02d-%04d %02d:%02d:%02d] (INFO) ",
                local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
                local->tm_hour, local->tm_min, local->tm_sec);
    }else if (logType == ERR) {
        fprintf(logFile, "[%02d-%02d-%04d %02d:%02d:%02d] (ERR) ",
                local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
                local->tm_hour, local->tm_min, local->tm_sec);
    }else if (logType == DEBUG) {
        fprintf(stdout, "[%02d-%02d-%04d %02d:%02d:%02d] (DEBUG)",
                local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
                local->tm_hour, local->tm_min, local->tm_sec);
        vfprintf(stdout, format, args);
        fprintf(stdout, "\n");
    }

    vfprintf(logFile, format, args);
    fprintf(logFile, "\n");
    va_end(args);
    closeLogger(logFile);

}

void closeLogger(FILE* logFile) {

    if (logFile != NULL) fclose(logFile);

}
