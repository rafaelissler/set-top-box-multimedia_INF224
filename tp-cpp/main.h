#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <memory>
#include <sstream>
#include <map>
#include "multimedia.h"
#include "video.h"
#include "film.h"
#include "photo.h"
#include "group.h"
#include "manager.h"
#include "tcp/tcpserver.h"

using namespace std;

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
    mngr.printAll(arg, ret);
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

#endif