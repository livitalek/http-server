#ifndef __DATA_PARSING_H
#define __DATA_PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StartLine {
    char *method;
    char *url;
    char *versionHttp;
} StartLine;

typedef struct Header {
    char *host;
    char *accept;
    char *acceptCharset;
    char *acceptEncoding;
    char *acceptLanguage;
    char *authorization;
    char *cacheControl;
    char *connection;
    int contentLength; 
    char *contentType;
    char *cookie;
} Header;

typedef struct Body {
    char *data; 
} Body;

typedef struct Request {
    StartLine startLine;
    Header header;
    Body body;
} Request;

void requestProcessing(char *data, Request *req);

void freeRequest(Request *req);

#endif