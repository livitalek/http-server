#ifndef __METHODS_GET_PUT_H
#define __METHODS_GET_PUT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "data_parsing.h"
#include "user_response.h"
#include "router.h"
#include "http_status.h"
#include "url_decoder.h"

void httpGet(char* responseMessage, Request *req, int routeId);
void httpPut(char* responseMessage, Request *req, int routeId);

#endif // __METHODS_GET_PUT_H