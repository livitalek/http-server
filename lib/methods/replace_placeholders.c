#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "replace_placeholders.h"

#define MAX_DATA 50
#define BUFFER_SIZE 512

int parseData(const char* str, Data dataArray[], int maxData) {

    char buffer[BUFFER_SIZE]; 
    strcpy(buffer, str); 
    char* token = strtok(buffer, "&"); 
    int count = 0;
    
    while (token != NULL && count < maxData) {
        char* equalSign = strchr(token, '='); 

        if (equalSign != NULL) {
            *equalSign = '\0'; 
            strncpy(dataArray[count].name, token, sizeof(dataArray[count].name));
            strncpy(dataArray[count].value, equalSign + 1, sizeof(dataArray[count].value));
            dataArray[count].value[sizeof(dataArray[count].value) - 1] = '\0';
            count++;
        }

        token = strtok(NULL, "&"); 
    }
    
    return count; 

}

const char* getValueByName(const Data dataArray[], int dataCount, const char* name) {

    for (int i = 0; i < dataCount; i++) {
        if (strcmp(dataArray[i].name, name) == 0) return dataArray[i].value; 
    }

    return NULL; 

}

void replacePlaceholders(const char* templateStr, const char* dataStr, char* result, int resultSize) {

    Data dataArray[MAX_DATA];
    int dataCount = parseData(dataStr, dataArray, MAX_DATA);
    snprintf(result, resultSize, "%s", templateStr);
    char tempResult[BUFFER_SIZE];
    char* placeholderStart = strstr(result, "{");

    while (placeholderStart != NULL) {
        char* placeholderEnd = strchr(placeholderStart, '}');

        if (placeholderEnd == NULL) break; 

        size_t placeholderLength = placeholderEnd - placeholderStart + 1; 
        char placeholder[128];
        strncpy(placeholder, placeholderStart, placeholderLength);
        placeholder[placeholderLength] = '\0'; 

        char key[128];
        snprintf(key, sizeof(key), "%.*s", (int)(placeholderLength - 2), placeholderStart + 1);
        const char* value = getValueByName(dataArray, dataCount, key);

        if (value != NULL) {
            snprintf(tempResult, BUFFER_SIZE, "%.*s%s%s", (int)(placeholderStart - result), result,
                     value, placeholderEnd + 1);
        } else {
            snprintf(tempResult, BUFFER_SIZE, "%.*s%s%s", (int)(placeholderStart - result), result,
                     placeholder, placeholderEnd + 1);
        }

        snprintf(result, resultSize, "%s", tempResult);
        placeholderStart = strstr(result, "{");
    }

}