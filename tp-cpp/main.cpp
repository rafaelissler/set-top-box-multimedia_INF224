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

/**
 * @brief Command to send to client contents of a group
 */
auto getGroup = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    getline(ss, arg, delim);
    stringstream ret;
    mngr.printGroup(arg, ret);
    return ret.str();
};

/**
 * @brief Command to send to client contents of a multimedia object
 */
auto getMedia = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    getline(ss, arg, delim);
    stringstream ret;
    mngr.printMultimedia(arg, ret);
    return ret.str();
};

/**
 * @brief Command to play a multimedia media object
 */
auto playMedia = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    getline(ss, arg, delim);
    mngr.play(arg);
    ss.str("OK!");
    return ss.str();
};

/**
 * @brief Command to send to client all objects with a given type
 */
auto getType = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    getline(ss, arg, delim);
    stringstream ret;
    mngr.printType(arg, ret);
    return ret.str();
};

/**
 * @brief Command to send to client all objects and groups with a given string in their name
 */
auto getHas = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    getline(ss, arg, delim);
    stringstream ret;
    mngr.printContains(arg, ret);
    return ret.str();
};

/**
 * @brief Command from a client to remove an object
 */
auto removeObj = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    getline(ss, arg, delim);
    return mngr.removeMultimedia(arg);
};

/**
 * @brief Command from a client to remove a group
 */
auto removeGroup = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    getline(ss, arg, delim);
    return mngr.removeGroup(arg);
};

/**
 * @brief Command from a client to create an object
 */
auto createObject = [](stringstream &ss, Manager &mngr) -> string {
    string type, arg;
    
    getline(ss, type, delim);
    int point = ss.tellg();
    getline(ss, arg, delim);
    ss.seekg(point, std::ios_base::beg);
    std::shared_ptr<Multimedia> obj = mngr.createMultimedia(type, arg);

    obj->readValues(ss);
    return "Created object " + arg;
};

/**
 * @brief Command from a client to create a group
 */
auto createGroup = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    getline(ss, arg, delim);
    mngr.createGroup(arg);
    return "Group " + arg + " created";
};

/**
 * @brief Command from a client to link an object to a group
 */
auto addToGroup = [](stringstream &ss, Manager &mngr) -> string {
    string arg;
    getline(ss, arg, delim);
    shared_ptr<Group> group = mngr.getGroupByName(arg);
    getline(ss, arg, delim);
    std::shared_ptr<Multimedia> object = mngr.getObjectByName(arg);
    group->push_back(object);
    return "Object linked to group " + arg;
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
    cmds.emplace("remove", removeObj);
    cmds.emplace("remove-group", removeGroup);
    cmds.emplace("create", createObject);
    cmds.emplace("create-group", createGroup);
    cmds.emplace("link", addToGroup);
};

int main(int argc, const char* argv[]) {
    // Initialize everything
    startupCmds();
    Manager mngr;

    std::ifstream file1("_objects2.txt");
    if (!file1) return 1;
    mngr.readFromFile(file1);
    file1.close();

    std::ofstream file2("_objects3.txt");
    if (!file2) return 1;
    mngr.printAllMultimedia(file2);
    file2.close();

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