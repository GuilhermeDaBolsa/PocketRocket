#include <iostream>
#include "../Crow_all.h"

using namespace crow;
using namespace std;

namespace controllers {
    class SocketController {
    public:
        void open(crow::websocket::connection& conn, const std::string& reason) {
            CROW_LOG_INFO << "websocket connection is open: " << reason;
        }
    };
}