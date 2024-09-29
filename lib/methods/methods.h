#ifndef __METHODS_H
#define __METHODS_H

#include <stdio.h>
#include <string.h>
#include "data_parsing.h"
#include "user_response.h"
#include "router.h"
#include "http_status.h"
#include "url_decoder.h"

void httpError(char* responseMessage, Request *req, int status);
void httpGet(char* responseMessage, Request *req, int routeId);
void httpPost(char* responseMessage, Request *req, int routeId);
void httpPut(char* responseMessage, Request *req, int routeId);
void httpDelete(char* responseMessage, Request *req, int routeId);
void httpHead(char* responseMessage, Request *req, int routeId);
int methods(char* responseMessage, char *requsetMessage);

#endif