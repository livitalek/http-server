#ifndef __ROUTER_H
#define __ROUTER_H

#include "data_parsing.h"
#include "user_response.h"

typedef UserResponse (*MethodPointer)(Request *request);

struct Route {
    char url[256]; 
    char methodType[10]; 
    MethodPointer method; 
} typedef Route;

int initRouter(int size);
int addRouteToRouter(Route route); 
int createMethod(const char* url, const char* methodType, UserResponse (*function)(Request *request)); 

int getRouteIdFromRouter(const char* url, const char* methodType); 
Route getRouteFromRouter(int routeId); 

int freeRouter();
#endif