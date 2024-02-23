#include "httplib.h"
#include <iostream>
#include <vector>
#include <mutex>
#include <string>

using namespace std;

void handleGet(const httplib::Request& req, httplib::Response& res){
    res.send("test")
}

void handlePost(const httplib::Request& req, httplib::Response& res){

}

int main(){
    httplib::Server app;

    app.Get('/', handleGet);

    app.listen("0.0.0.0", 8080);

    return 0;
}