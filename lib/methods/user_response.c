#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include "user_response.h"
#include "http_status.h"
#include "replace_placeholders.h"


static char dirPath[512] = "html/";

void setDirectoryHtmlPath(char* directoryPath) {
    
    if (directoryPath == NULL) {
        strcpy(dirPath, "");
        return;
    }

    if (opendir(directoryPath) == NULL) exit(EXIT_FAILURE);
    strcpy(dirPath, directoryPath);
    
    size_t len = strlen(dirPath);

    if (len > 0 && dirPath[len - 1] != '/') {
        dirPath[len] = '/';
        dirPath[len + 1] = '\0';
    }

}

UserResponse responseHtmlFile(int status, char *htmlFile) {
 
    FILE *file;
    char line[256];
    char *message = NULL;
    size_t messageLength = 0;
    UserResponse userResponse;
    
    if ((userResponse.status = getStatus(status).code) != status) {
        sprintf(userResponse.message, "%s\nError status %d not found\n", getStatus(userResponse.status).description, status);
        return userResponse;
    }

    char fileName[512];
    sprintf(fileName, "%s%s", dirPath, htmlFile);

    if ((file = fopen(fileName, "r")) == NULL) {
        userResponse.status = getStatus(500).code;
        sprintf(userResponse.message, "%s\nError file dont't open (%s)\n", getStatus(500).description, htmlFile);
        return userResponse;
    }

    while (fgets(line, sizeof(line), file)) {
        size_t lineLength = strlen(line);
        char *newMessage = realloc(message, messageLength + lineLength + 1);
        
        if (newMessage == NULL) {
            userResponse.status = getStatus(500).code;
            sprintf(userResponse.message, "%s\nError memory allocation error\n", getStatus(500).description);
            free(message);
            fclose(file);
            return userResponse;
        }

        message = newMessage;
        strcpy(message + messageLength, line);
        messageLength += lineLength;
    }

    fclose(file);
    userResponse.status = status;
    strcpy(userResponse.message, message);
    free(message);
    return userResponse;

}

UserResponse responseHtmlFileTemplate(int status, char *htmlFile, char*data) {

    FILE *file;
    char line[512];
    char buffLine[256];
    char *message = NULL;
    size_t messageLength = 0;
    UserResponse userResponse;

    if ((userResponse.status = getStatus(status).code) != status) {
        sprintf(userResponse.message, "%s\nError status %d not found\n", getStatus(userResponse.status).description, status);
        return userResponse;
    }

    char fileName[512];
    sprintf(fileName, "%s%s", dirPath, htmlFile);

    if ((file = fopen(fileName, "r")) == NULL) {
        userResponse.status = getStatus(500).code;
        sprintf(userResponse.message, "%s\nError file dont't open (%s)\n", getStatus(500).description, htmlFile);
        return userResponse;
    }

    while (fgets(buffLine, sizeof(buffLine), file)) {
        replacePlaceholders(buffLine, data, line, 512);
        size_t lineLength = strlen(line);
        char *newMessage = realloc(message, messageLength + lineLength + 1);
        
        if (newMessage == NULL) {
            userResponse.status = getStatus(500).code;
            sprintf(userResponse.message, "%s\nError memory allocation error\n", getStatus(500).description);
            free(message);
            fclose(file);
            return userResponse;
        }

        message = newMessage;
        strcpy(message + messageLength, line);
        messageLength += lineLength;
    }

    fclose(file);
    userResponse.status = status;
    strcpy(userResponse.message, message);
    free(message);
    return userResponse;

}

UserResponse responseText(int status, char *text) {

    UserResponse userResponse;

    if ((userResponse.status = getStatus(status).code) != status) {
        sprintf(userResponse.message, "%s\nError status %d not found\n", getStatus(userResponse.status).description, status);
        return userResponse;
    }

    userResponse.status = status;
    strcpy(userResponse.message, text);
    return userResponse;

}

UserResponse responseTextTemplate(int status, char *text, char *data) {

    char resultText[512];
    replacePlaceholders(text, data, resultText, 512);
    UserResponse userResponse;
    
    if ((userResponse.status = getStatus(status).code) != status) {
        sprintf(userResponse.message, "%s\nError status %d not found\n", getStatus(userResponse.status).description, status);
        return userResponse;
    }

    userResponse.status = status;
    strcpy(userResponse.message, resultText);
    return userResponse;

}
