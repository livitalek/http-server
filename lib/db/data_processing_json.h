#ifndef __DATA_PROCCESING_JSON_H
#define __DATA_PROCCESING_JSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON-master/cJSON.h"

#define FILE_NAME "data.json"
#define FILE_CONFIG_NAME "config.json"
#define MAX_FIELDS 32

typedef struct KeyValuePair {
    char *key;
    char *value;
} KeyValuePair;

typedef struct DataFields {
    KeyValuePair pairs[MAX_FIELDS];
    int count;
} DataFields;

void pullConfig(DataFields **data);

void parseQueryString(char *queryString, DataFields **bodyFields);

void saveJsonData(char *body);

cJSON* loadJsonData();

void freeDataFields(DataFields *data, int flag);

int booleanUser(cJSON *jsonArray, char *value, char *primaryKey);

int readJson(char* body);

char* updateUser(char* body);

void loadFile(cJSON *jsonArray);

#endif //__DATA_PROCCESING_JSON_H