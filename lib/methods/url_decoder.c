#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "url_decoder.h"


char *urlDecode(const char *url) {
    
    if (url == NULL) return NULL;
    size_t len = strlen(url);
    char *decoded = malloc(len + 1);
    if (!decoded) return NULL;
    char *p = decoded;

    for (size_t i = 0; i < len; i++) {

        if (url[i] == '%' && i + 2 < len) {
            int value;

            if (sscanf(url + i + 1, "%2x", &value) == 1) {
                *p++ = (char)value;
                i += 2;
            } else {
                *p++ = url[i];
            }

        } else if (url[i] == '+') {
            *p++ = ' ';
        } else {
            *p++ = url[i];
        }

    }

    *p = '\0';
    return decoded;

}