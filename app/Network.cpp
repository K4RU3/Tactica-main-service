#include <memory>

#include <boost/asio.hpp>
#include <boost/beast/websocket.hpp>
#include <uuid_v4.h>

using namespace boost::asio;
using namespace boost::beast::websocket;
using ClientPair = std::pair<UUIDv4::UUID, stream<ip::tcp::socket>>;
using ClientShared = std::shared_ptr<ClientPair>;

class Network{
public:
    Network(): io(), endpoint(ip::address::from_string("0.0.0.0"), 8080){
        
    }

    ClientShared accept(){
        

    }

private:
    io_context io;
    ip::tcp::endpoint endpoint;
};