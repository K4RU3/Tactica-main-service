#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

#include <uuid_v4.h>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

//定義域
UUIDv4::UUIDGenerator<mt19937_64> uuidGenerator;

/* ===== Class ===== */
class Server{
public:
    Server(boost::asio::io_context& io, short port)
        :_acceptor(io, tcp::endpoint(tcp::v4(), port)),
        _socket(io)
        {
            accept();
        }

private:
    void accept(){
        _acceptor.async_accept(_socket,
            [this](boost::system::error_code ec){
                if(!ec){
                    make_shared<Session>(move(_socket))->start();
                }
                accept();
            });
    }

    tcp::acceptor _acceptor;
    tcp::socket _socket;
};

class Session : public enable_shared_from_this<Session>{
public:
    Session(tcp::socket socket) : _socket(move(socket)) {}

    void start(){
        read();
    }

private:
    void read(){
        auto self(shared_from_this());
        
    }

    tcp::socket _socket;
};

/* ===== main ===== */
int main(){
    

    return 0;
}