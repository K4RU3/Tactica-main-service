#include "httplib.h"
#include <iostream>

int main() {
    // Create an HTTP server
    httplib::Server svr;

    // Define a handler for the root path
    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("Hello, World!", "text/plain");
    });

    // Start the server on port 8080
    svr.listen("0.0.0.0", 8080);

    return 0;
}