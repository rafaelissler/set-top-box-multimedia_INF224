
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

    if (obj->getName() != arg || obj == nullptr) return "Error: Please use the correct format";

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
    if (group == nullptr) return "Group not found: " + arg;

    getline(ss, arg, delim);
    std::shared_ptr<Multimedia> object = mngr.getObjectByName(arg);
    if (object == nullptr) return "Object not found: " + arg;

    group->push_back(object);
    return "Object " + arg + "linked to group " + group->getName();
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