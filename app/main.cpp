#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

#include "uuid_v4.h"
#include "httplib.h"

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
            res.set_content(uuidGenerator.getUUID().str(), "text/plain");
        }
    });

    app.Get("/sse", [](const Request& req, Response& res){
        int count;
        try{
            count = stoi(req.get_param_value("count"));
        }catch(const exception& e){
            count = 10;
        }

        res.set_header("Content-Type", "text/event-stream");

        res.set_chunked_content_provider(
            "text/event-stream",
            [&count](size_t offset, DataSink &sink){
                for(int i = 0; i < count; i++){
                    this_thread::sleep_for(chrono::seconds(1));
                    string uuid = "data: " + uuidGenerator.getUUID().str() + "\n\n";
                    sink.write(uuid.c_str(), uuid.size());
                }
                return true;
            }
        );
    });

    thread server([&app](){
        app.listen("0.0.0.0", 8080);
    });

    server.join();

    return 0;
}