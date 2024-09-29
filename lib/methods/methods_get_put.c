#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "data_parsing.h"
#include "user_response.h"
#include "router.h"
#include "http_status.h"
#include "url_decoder.h"
#include "methods.h"

void httpGet(char* responseMessage, Request *req, int routeId) {

    Route route = getRouteFromRouter(routeId);
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

void httpPut(char* responseMessage, Request *req, int routeId) {

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