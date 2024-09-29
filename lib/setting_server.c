#include <stdlib.h>
#include <stdio.h>
#include "methods/methods.h"
#include "methods/router.h"
#include "methods/user_response.h"
#include "methods/data_parsing.h"
#include "db/data_processing_json.h"

UserResponse methodGet(Request *req) {

    return responseHtmlFile(200,"index.html");

}

UserResponse methodPost(Request *req) {

    saveJsonData(req->body.data);
    return responseHtmlFile(200,"index.html");

}


UserResponse registerGet(Request *req) {

    return responseHtmlFile(200,"register.html");

}

UserResponse homePost(Request *req) {

    
    printf("%d\n", readJson(req->body.data));
    if (readJson(req->body.data) == 0) return responseHtmlFile(401, "html_status/401.html");
    else return responseHtmlFileTemplate(200,"home.html", req->body.data);
}


void settingServer() {
    setDirectoryHtmlPath("html_pages/");
    createMethod("/", "GET", methodGet);
    createMethod("/", "POST", methodPost);
    createMethod("/register/", "GET", registerGet);    
    createMethod("/home/", "POST", homePost);

}