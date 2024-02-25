#include <iostream>
#include "uuid_v4.h"
#include "httplib.h"
#include <string>
#include <thread>
#include <chrono>

using namespace std;
using namespace httplib;

//定義域
UUIDv4::UUIDGenerator<mt19937_64> uuidGenerator;

int main(){
    Server app;

    app.set_default_headers({
        {"Access-Control-Allow-Origin", "*"}
    });

    app.Get("/", [](const Request& req, Response& res){
        try{
            int count = stoi(req.get_param_value("count"));
            string value;
            for(int i = 0; i < count; i++){
                value += uuidGenerator.getUUID().str() + "\n";
            }
            res.set_content(value, "text/plain");
        }catch(const exception& e){
            res.set_content("Invlid the body", "text/plain");
        }
    });

    app.listen("localhost", 8080);
    return 0;
}