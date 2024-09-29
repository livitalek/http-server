#ifndef __USER_RESPONSE_H
#define __USER_RESPONSE_H

typedef struct UserResponse{
    int status;
    char message[51200];
} UserResponse;

void setDirectoryHtmlPath(char* directoryPath);

UserResponse responseHtmlFile(int status, char *htmlFile);
UserResponse responseHtmlFileTemplate(int status, char *htmlFile, char *data);
UserResponse responseText(int status, char *text);
UserResponse responseTextTemplate(int status, char *text, char *data);

#endif