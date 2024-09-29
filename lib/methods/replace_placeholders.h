#ifndef __REPLACE_PLACEHOLDERS_H
#define __REPLACE_PLACEHOLDERS_H

struct Data {
    char name[32];
    char value[32];
} typedef Data;

int parseData(const char* str, Data dataArray[], int maxData);
const char* getValueByName(const Data dataArray[], int dataCount, const char* name);
void replacePlaceholders(const char* templateStr, const char* dataStr, char* result, int resultSize);

#endif