#include <iostream>
#include <memory>
#include <sstream>
#include <map>
#include "../multimedia.h"
#include "../video.h"
#include "../film.h"
#include "../photo.h"
#include "../group.h"
#include "../manager.h"
#include "tcpserver.h"

using namespace std;

const int PORT = 4466;
const char delim = '|';

/**
 * @brief Command to send to client contents of a group
 */
auto getGroup = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    ss >> arg;
    stringstream ret;
    mngr.printGroup(arg, ret);
    return ret.str();
};

/**
 * @brief Command to send to client contents of a multimedia object
 */
auto getMedia = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    ss >> arg;
    stringstream ret;
    mngr.printMultimedia(arg, ret);
    return ret.str();
};

/**
 * @brief Command to play a multimedia media object
 */
auto playMedia = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    ss >> arg;
    mngr.play(arg);
    ss.str("OK!");
    return ss.str();
};

/**
 * @brief Command to send to client all objects with a given type
 */
auto getType = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    ss >> arg;
    stringstream ret;
    mngr.printType(arg, ret);
    return ret.str();
};

/**
 * @brief Command to send to client all objects and groups with a given string in their name
 */
auto getHas = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    ss >> arg;
    stringstream ret;
    mngr.printContains(arg, ret);
    return ret.str();
};

map<string,function<string(stringstream&, Manager&)>> cmds;

/**
 * @brief Assign the lambda commands with command name
 */
auto startupCmds = []() {
    cmds.emplace("get-group", getGroup);
    cmds.emplace("get", getMedia);
    cmds.emplace("play", playMedia);
    cmds.emplace("get-type", getType);
    cmds.emplace("get-has", getHas);
};

int main(int argc, const char* argv[]) {
    // Initialize everything
    startupCmds();
    Manager mngr;

    int chapters[5];
    for (int i = 0; i < 5; i++) chapters[i] = i+1;
    shared_ptr<Film> f = mngr.createFilm("avatar", "film.mov", 10, chapters, 5);
    shared_ptr<Photo> p1 = mngr.createPhoto("github", "photo1.png", 3.3, 7);
    shared_ptr<Photo> p2 = mngr.createPhoto("gnu", "photo2.png", 3.7, 4);
    shared_ptr<Video> v1 = mngr.createVideo("telecom", "video.mp4", 5);
    shared_ptr<Video> v2 = mngr.createVideo("gitlab", "video2.mp4", 7);

    shared_ptr<Group> group = mngr.createGroup("toto");
    group->push_back(f);
    group->push_back(p1);
    group->push_back(v1);

    shared_ptr<Group> group2 = mngr.createGroup("titi");
    group2->push_back(f);
    group2->push_back(p2);
    group2->push_back(v2);

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
        ss >> arg;  // Get first argument

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