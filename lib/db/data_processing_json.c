#include "data_processing_json.h"

void saveJsonData(char *body) {

    DataFields *config = NULL,*bodyFields = NULL;

    cJSON *json = loadJsonData();

    pullConfig(&config);
    parseQueryString(body,&bodyFields);

    cJSON *user = cJSON_CreateObject();

    for(int i = 0; i < config->count; i++) {

        for(int j = 0; j < bodyFields->count;j++) {
            
            if(strcmp(bodyFields->pairs[j].key,config->pairs[i].key) == 0) {
                if(booleanUser(json,bodyFields->pairs[j].value,config->pairs[0].key)) return;
                cJSON_AddStringToObject(user, config->pairs[i].key, bodyFields->pairs[j].value);
                break;
            }

        }
        
    }

    cJSON_AddItemToArray(json, user);
    loadFile(json);

    freeDataFields(config,1);
    freeDataFields(bodyFields,0);
    cJSON_Delete(json);

}

void loadFile(cJSON *json){

    FILE *file = fopen(FILE_NAME, "w");

    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    char *jsonString = cJSON_Print(json);

    if (jsonString) {
        fprintf(file, "%s\n", jsonString);
        free(jsonString);
    }

    fclose(file);

}
void freeDataFields(DataFields *data,int flag) {

    if (data == NULL) return; 
    
    for (int i = 0; i < data->count; i++) {
        free(data->pairs[i].key);
        if(flag == 0) free(data->pairs[i].value);
    }

    free(data);

}

int booleanUser(cJSON *jsonArray, char *value,char *primaryKey) {

    if(!jsonArray) return 0;

    for(int i = 0; i < cJSON_GetArraySize(jsonArray);i++) {
        cJSON *jsonUser = cJSON_GetArrayItem(jsonArray, i);
        if(strcmp(strdup(cJSON_GetObjectItem(jsonUser, primaryKey)->valuestring), value) == 0) return 1;
    }

    return 0;

}

void parseQueryString(char *queryString, DataFields **bodyFields) {

    int pairCount = 0;
    const char *ptr = queryString;
    
    while (*ptr) {
        if (*ptr == '&') pairCount++;
        ptr++;
    }

    pairCount++; 

    *bodyFields = malloc(sizeof(DataFields));
    (*bodyFields)->count = pairCount;
    
    char *queryCopy = strdup(queryString);
    char *token = strtok(queryCopy, "&");
    int index = 0;
    
    while (token != NULL) {
        char *equalSign = strchr(token, '=');

        if (equalSign) {
            *equalSign = '\0'; 
            (*bodyFields)->pairs[index].key = strdup(token);
            (*bodyFields)->pairs[index].value = strdup(equalSign + 1);
            index++;
        }

        token = strtok(NULL, "&");
    }

    free(queryCopy);

}

cJSON* loadJsonData() {

    FILE *file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        perror("Error opening file for reading");
        exit(0);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *json_string = malloc(length + 1);
    fread(json_string, 1, length, file);
    json_string[length] = '\0'; 

    fclose(file); 

    cJSON *jsonArray = cJSON_Parse(json_string);
    free(json_string);

    if(!jsonArray) {
        jsonArray = cJSON_CreateArray();
    }

    return jsonArray;

}

void pullConfig(DataFields **config) {

    FILE *file = fopen(FILE_CONFIG_NAME, "r");

    if (!file) {
        perror("Error opening config file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *jsonString = malloc(length + 1);
    fread(jsonString, 1, length, file);
    jsonString[length] = '\0';

    fclose(file);

    cJSON *json = cJSON_Parse(jsonString);
    free(jsonString);

    cJSON *jsonFields = cJSON_GetObjectItem(json, "fields");
    *config = malloc(sizeof(DataFields));

    (*config)->count = cJSON_GetArraySize(jsonFields);

    for (int i = 0; i < (*config)->count; i++) {
        (*config)->pairs[i].key = strdup(cJSON_GetArrayItem(jsonFields, i)->valuestring);
    }

    cJSON_Delete(json);

}

int readJson(char *body) {

    DataFields *config = NULL,*bodyFields = NULL;

    cJSON *jsonArray = loadJsonData();
    pullConfig(&config);
    parseQueryString(body,&bodyFields);


    for(int i = 0; i < cJSON_GetArraySize(jsonArray);i++) {
        cJSON *jsonUser = cJSON_GetArrayItem(jsonArray, i);
            if(cJSON_GetObjectItem(jsonUser, bodyFields->pairs[1].key) != NULL && strcmp(cJSON_GetObjectItem(jsonUser, bodyFields->pairs[0].key)->valuestring,bodyFields->pairs[0].value) == 0){

                if(strcmp(cJSON_GetObjectItem(jsonUser, bodyFields->pairs[1].key)->valuestring,bodyFields->pairs[1].value) == 0){
                    return 1;
                }
            }
            
    }

    return 0;
}

char* updateUser(char* body){

    DataFields *config = NULL,*bodyFields = NULL;

    cJSON *jsonArray = loadJsonData();
    pullConfig(&config);
    parseQueryString(body,&bodyFields);

    if(strcmp(bodyFields->pairs[1].key,"attribute") != 0 || strcmp(bodyFields->pairs[2].key,"new") != 0 ) return "Invalid command";

    for(int i = 0; i < cJSON_GetArraySize(jsonArray);i++) {
        cJSON *jsonUser = cJSON_GetArrayItem(jsonArray, i);

        if(strcmp(cJSON_GetObjectItem(jsonUser, config->pairs[0].key)->valuestring, bodyFields->pairs[0].value) == 0){

            if(cJSON_GetObjectItem(jsonUser, bodyFields->pairs[1].value) != NULL){
                cJSON_SetValuestring(cJSON_GetObjectItem(jsonUser,bodyFields->pairs[1].value),bodyFields->pairs[2].value);
                loadFile(jsonArray);
                return cJSON_GetObjectItem(jsonUser, bodyFields->pairs[1].value)->valuestring;
            }

        }
            
    }

    return "Not found";

}

