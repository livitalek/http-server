#include "data_parsing.h"

void requestProcessing(char *data,Request *req){

    char *dataCopy = strdup(data);
    char *startLine = strtok(dataCopy, "\r\n");

    if (startLine) {
        req->startLine.method = strdup(strtok(startLine, " "));
        req->startLine.url = strdup(strtok(NULL, " "));
        req->startLine.versionHttp = strdup(strtok(NULL, " "));
    }

    char *line = strtok(data, "\r\n");

    while ((line = strtok(NULL, "\r\n")) != NULL && strlen(line) > 0) {
        if (strncmp(line, "Host:", 5) == 0) {
            req->header.host = line+6; 
        } else if (strncmp(line, "Accept:", 7) == 0) {
            req->header.accept = line + 8; 
        } else if (strncmp(line, "Accept-Charset:", 15) == 0) {
            req->header.acceptCharset = line + 16; 
        } else if (strncmp(line, "Accept-Encoding:", 16) == 0) {
            req->header.acceptEncoding = line + 17; 
        } else if (strncmp(line, "Accept-Language:", 16) == 0) {
            req->header.acceptLanguage = line + 17; 
        } else if (strncmp(line, "Authorization:", 14) == 0) {
            req->header.authorization = line + 15; 
        } else if (strncmp(line, "Cache-Control:", 14) == 0) {
            req->header.cacheControl = line + 15; 
        } else if (strncmp(line, "Connection:", 11) == 0) {
            req->header.connection = line + 12; 
        } else if (strncmp(line, "Content-Length:", 15) == 0) {
            req->header.contentLength = atoi(line + 16); 
        } else if (strncmp(line, "Content-Type:", 13) == 0) {
            req->header.contentType = line + 14; 
        } else if (strncmp(line, "Cookie:", 7) == 0) {
            req->header.cookie = line + 8;             
        } else {
            req->body.data = line;
        }
    }   
    
    free(dataCopy);

}

void freeRequest(Request *req) {
    
    free(req->startLine.method);
    free(req->startLine.url);
    free(req->startLine.versionHttp);

    free(req->header.host);
    free(req->header.accept);
    free(req->header.acceptCharset);
    free(req->header.acceptEncoding);
    free(req->header.acceptLanguage);
    free(req->header.authorization);
    free(req->header.cacheControl);
    free(req->header.connection);
    free(req->header.contentType);
    free(req->header.cookie);

    free(req->body.data);
    
}