#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "router.h"
#include "data_parsing.h"
#include "user_response.h"

static Route *routes;
static int numberOfRoutes;
static int routePosition;

int initRouter(int size) {
    
    numberOfRoutes = ((size > 100) ? size : 100) * 5 ;
    routes = (Route*) malloc (numberOfRoutes * sizeof(Route));
    routePosition = 0;
    return 0;

}

int addRouteToRouter(Route route) {
    
    //Check if the route list is overloaded
    if (routePosition >= numberOfRoutes) return -1;
    
    //Check if the route don't have those methods
    if (strcmp(route.methodType, "GET") != 0 && strcmp(route.methodType, "POST") != 0 &&
        strcmp(route.methodType, "PUT") != 0 && strcmp(route.methodType, "DELETE") != 0 &&
        strcmp(route.methodType, "HEAD") != 0) return -2;

    int i = 0;
     
    //Check if user method is already created by URL
    for (i = 0; i < routePosition; i++) {
        if (strcmp(routes[i].url, route.url) == 0 && strcmp(routes[i].methodType, route.methodType) == 0) return -3;
    }

    strcpy(routes[routePosition].url, route.url);
    strcpy(routes[routePosition].methodType, route.methodType);
    routes[routePosition].method = route.method;
    routePosition++;
    return 0;

}

int createMethod(const char* url, const char* methodType, UserResponse (*function)(Request *request)) {
    
    Route route;
    strcpy(route.url, url);
    strcpy(route.methodType, methodType);
    route.method = function;
    return addRouteToRouter(route);

}

int getRouteIdFromRouter(const char* url, const char* methodType) {
    
    int i = 0;

    for (i = 0; i < routePosition; i++) {
        if (strcmp(url, routes[i].url) == 0 && strcmp(methodType, routes[i].methodType) == 0) return i;
    }

    return -1;

} 

Route getRouteFromRouter(int routeId) {
    
    if (routeId < 0 || routeId >= routePosition) {
        Route route;
        return route;
    }
    
    return routes[routeId];

}


int freeRouter() {
    
    free(routes);

}
