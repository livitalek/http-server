#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_parsing.h"
#include "user_response.h"
#include "router.h"
#include "http_status.h"
#include "url_decoder.h"
#include "methods.h"

void httpError(char* responseMessage, Request *req, int status) {

    char data[128];
    sprintf(data, "status=%d&description=%s\n", status, getStatus(status).description);
    UserResponse userResponse = responseHtmlFileTemplate(status, "error/error_temp.html", data);
    int contentLength = strlen(userResponse.message);
    char connection[20];

    if (req->header.connection == NULL || status >= 500) {
        strcpy(connection, "close");
    } else {
        strcpy(connection, req->header.connection);
    }

    sprintf(responseMessage,
            "HTTP/1.1 %d %s\r\n" 
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: %d\r\n"
            "Connection: %s\r\n"
            "\r\n"
            "%s",
            userResponse.status, getStatus(userResponse.status).description , contentLength, connection, userResponse.message);

}

void httpPost(char* responseMessage, Request *req, int routeId) {

    Route route = getRouteFromRouter(routeId);
    req->body.data = urlDecode(req->body.data);
    UserResponse userResponse = route.method(req);
    int contentLength = strlen(userResponse.message);
    char connection[20];

    if (req->header.connection == NULL) {
        strcpy(connection, "close");
    } else {
        strcpy(connection, req->header.connection);
    }

    sprintf(responseMessage,
            "HTTP/1.1 %d %s\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: %d\r\n"
            "Connection: %s\r\n"
            "\r\n"
            "%s",
            userResponse.status, getStatus(userResponse.status).description , contentLength, connection, userResponse.message); 

}

void httpDelete(char* responseMessage, Request *req, int routeId) {

    Route route = getRouteFromRouter(routeId);
    req->body.data = urlDecode(req->body.data);
    UserResponse userResponse = route.method(req);
    int contentLength = strlen(userResponse.message);
    char connection[20];

    if (req->header.connection == NULL) {
        strcpy(connection, "close");
    } else {
        strcpy(connection, req->header.connection);
    }

    sprintf(responseMessage,
            "HTTP/1.1 %d %s\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: %d\r\n"
            "Connection: %s\r\n"
            "\r\n"
            "%s",
            userResponse.status, getStatus(userResponse.status).description , contentLength, req->header.connection, userResponse.message); 

}

void httpHead(char* responseMessage, Request *req, int routeId) {
    
    Route route = getRouteFromRouter(routeId);
    req->body.data = urlDecode(req->body.data);
    UserResponse userResponse = route.method(req);
    int contentLength = strlen(userResponse.message);
    char connection[20];

    if (req->header.connection == NULL) {
        strcpy(connection, "close");
    } else {
        strcpy(connection, req->header.connection);
    }

    sprintf(responseMessage,
            "HTTP/1.1 %d %s\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: %d\r\n"
            "Connection: %s\r\n"
            "\r\n",
            userResponse.status, getStatus(userResponse.status).description, contentLength, req->header.connection); // Аргументы для замены

}

int methods(char* responseMessage, char *requsetMessage) {
    
    Request *req = malloc(sizeof(Request));
    memset(req, 0, sizeof(Request));

    char *dataCopy = strdup(requsetMessage);
    requestProcessing(dataCopy, req);
    free(dataCopy);
    int routeId = getRouteIdFromRouter(req->startLine.url, req->startLine.method);
    int connnection = (strcmp(req->header.connection, "Keep-Alive") == 0) ? 1 : 0; 

    if (strcmp("HTTP/1.1", req->startLine.versionHttp) != 0) {
        httpError(responseMessage, req, 505);
        //freeRequest(req);
        return 0;
    }

    if (routeId < 0) {
        httpError(responseMessage, req, 404);
        //freeRequest(req);
        return connnection;
    }


    if (strcmp(req->startLine.method, "GET") == 0) {
        httpGet(responseMessage, req, routeId); // условно Софина функция
    } else if (strcmp(req->startLine.method, "POST") == 0) {
        httpPost(responseMessage, req, routeId);
    } if (strcmp(req->startLine.method, "PUT") == 0) {
        httpPut(responseMessage, req, routeId); // условно Софина функция
    } else if (strcmp(req->startLine.method, "DELETE") == 0) {
        httpDelete(responseMessage, req, routeId); 
    } else if (strcmp(req->startLine.method, "HEAD") == 0) {
        httpHead(responseMessage, req, routeId); 
    }

//    freeRequest(req);
    return connnection; 

}