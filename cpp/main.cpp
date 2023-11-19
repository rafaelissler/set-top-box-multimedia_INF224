#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <map>
#include "multimedia.h"
#include "video.h"
#include "film.h"
#include "photo.h"
#include "group.h"
#include "manager.h"
#include "tcpserver.h"

using namespace std;

const int PORT = 4466;
const char delim = '|';

#include "commands.h"

int main(int argc, const char* argv[]) {
    // Initialize everything
    startupCmds();
    Manager mngr;

    std::ifstream file1("_objects.txt");
    if (!file1) return 1;
    mngr.readFromFile(file1);
    file1.close();

    // Define the callback of server
    shared_ptr<TCPServer> server = make_shared<TCPServer>([&]
    (std::string const& request, std::string& response) {
        #ifdef DEBUG
        cout << "[D] Request received: " << request << endl;
        #endif
        // Default response
        response = "OK";

        stringstream ss(request);
        string arg;
        getline(ss, arg, delim);  // Get first argument
        #ifdef DEBUG
        cout << arg << '\n';
        #endif

        // If it failed or client wants to quit, disconnect
        if (!ss.fail() && arg != "quit") {
            auto it = cmds.find(arg);
            if (it != cmds.end()) {
                // If it finds the request
                if (!ss.fail()) {
                    // Call the lambda associated with request
                    response = it->second(ss, mngr);
                    #ifdef DEBUG
                    std::cout << "[D] What will be sent: " << response << '\n';
                    #endif
                }
            } else {
                response = "Error: Could not understand " + arg;
                std::cout << response << '\n';
            }
        }
        else {
            response = "ERROR";
        }
        ss.str("");

        return true;
    });

    cout << "Opening server on port " << PORT << '\n';
    int err = server->run(PORT);
    if (err < 0) {
        cout << "Error: Server could not be started\n";
        return 1;
    }

    cout << "Finished succesfully\n";
    return 0;
}