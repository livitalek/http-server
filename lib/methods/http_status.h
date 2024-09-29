#ifndef __HTTP_STATUS_H
#define __HTTP_STATUS_H

struct HttpStatus {
    int code;
    char *description;
} typedef HttpStatus;

HttpStatus getStatus(int code);

#endif  