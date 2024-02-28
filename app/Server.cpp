#include <map>

#include <boost/beast.hpp>
#include <uuid_v4.h>

#include "Room.cpp"

using namespace std;
using boost::asio::ip::tcp;

class Server{
public:
    void openServer(){

    }

    void closeServer(){

    }

    void createRoom(UUIDv4::UUID){

    }

    void removeRoom(UUIDv4::UUID){

    }

private:
    map<UUIDv4::UUID, Room> roomList;
};