#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>
#include "multimedia.h"
#include "video.h"
#include "film.h"
#include "photo.h"
#include "group.h"
#include "manager.h"

extern const char delim;

Manager::~Manager() {}
Manager::Manager() {}

std::shared_ptr<Group> Manager::createGroup(std::string name) {
    // If it exists a group with same name, return nullptr
    auto found = groups.find(name);
    if (found != groups.end()) return nullptr;

    groups.emplace(name, std::make_shared<Group>(name));
    return groups[name];
}

std::shared_ptr<Photo> Manager::createPhoto(std::string name, std::string filePath,
float lat, float lon) {
    // If it exists an object with same name, returns an empty object without name
    auto found = objects.find(name);
    if (found != objects.end()) return std::make_shared<Photo>();

    std::shared_ptr<Photo> obj = std::make_shared<Photo>(name, filePath, lat, lon);
    objects.emplace(name, obj);
    return obj;
}

std::shared_ptr<Video> Manager::createVideo(std::string name, std::string filePath,
int duration) {
    // If it exists an object with same name, return an empty object without name
    auto found = objects.find(name);
    if (found != objects.end()) return std::make_shared<Video>();

    std::shared_ptr<Video> obj = std::make_shared<Video>(name, filePath, duration);
    objects.emplace(name, obj);
    return obj;
}

std::shared_ptr<Film> Manager::createFilm(std::string name, std::string filePath,
int duration, int* chapters, int numChapters) {
    // If it exists an object with same name, return an empty object without name
    auto found = objects.find(name);
    if (found != objects.end()) return std::make_shared<Film>();

    std::shared_ptr<Film> obj = std::make_shared<Film>(name, filePath, duration, chapters, numChapters);
    objects.emplace(name, obj);
    return obj;
}

std::shared_ptr<Multimedia> Manager::createMultimedia(std::string nameType, std::string name) {
    if (nameType == "photo") {
        return createPhoto(name, "", 0, 0);
    } else if (nameType == "video") {
        return createVideo(name, "", 0);
    } else if (nameType == "film") {
        return createFilm(name, "", 0, nullptr, 0);
    } else {
        return nullptr;
    }
}

void Manager::readFromFile(std::istream &in) {
    std::string buf;
    std::string groupToLink = "";

    // createMultimedia() needs a name for the object so the functions createFilm(),
    // createPhoto(), createPhoto() and createGroup() can use it as key for the map
    // of multimedia objects/groups, so we will peek the name on the file

    while (std::getline(in, buf, delim)) {
        // Will check if it's: a group, a "no group" indicator or if it's a multimedia object
        if (buf == "group") {
            std::getline(in, buf, delim);
            // Create group. If we already created this group, just continue the loop
            std::shared_ptr<Group> group = createGroup(buf);
            if (group == nullptr) continue;
            groupToLink = buf;
        }
        else if (buf == "no groups") {
            groupToLink = "";
        }
        else {
            // Mark the current spot on the file, peek the name of object and then return
            // to the previous spot on the file
            std::string namePeek;
            int point = in.tellg();
            std::getline(in, namePeek, delim);
            in.seekg(point, std::ios_base::beg);

            // Create object. If we already created this object, just continue the loop
            std::shared_ptr<Multimedia> obj = createMultimedia(buf, namePeek);
            obj->readValues(in);
            if (obj->getName() == "") continue;
            
            // If we need to link this object to a group, do it now
            if (groupToLink != "") {
                std::shared_ptr<Group> group = getGroupByName(groupToLink);
                if (group == nullptr) continue;
                group->push_back(obj);
            }
        }
    }
}

void Manager::printMultimedia(std::string name, std::ostream &out) const {
    auto it = objects.find(name);

    if (it != objects.end()) {
        out << it->second->getType() << delim;
        it->second->printValues(out);
    } else {
        out << "Error: Multimedia object of name " << name << " not found";
    }
}

void Manager::printAllMultimedia(std::ostream &out) const {
    printContains("", out);
}

void Manager::printType(std::string type, std::ostream &out) const {
    // Iterate through media objects and print the ones with the given type
    for (const auto& it : objects) {
        if (it.second->getType() == type) {
            out << it.second->getType() << delim;
            it.second->printValues(out);
        }
    }
}

void Manager::printContains(std::string name, std::ostream &out) const {
    std::vector<std::string> alreadyPrinted;
    
    // Only print "no groups" if a group was printed at all. Otherwise, there's no need
    int printNoGroups = 0;

    // Print the groups with the name (including their objects)
    for (const auto& it : groups) {
        if (it.first.find(name) != std::string::npos) {
            printNoGroups = 1;
            // If the group has a string in its name, print it
            out << "group" << delim;
            it.second->printValues(out);
            // Traverse through all objects in the group, set them as "already printed"
            for (const auto& obj : *(it.second)) {
                alreadyPrinted.push_back(obj->getName());
            }
        }
    }

    // Search through the multimedia objects without groups
    for (const auto& it : objects) {
        // Find if the object was already printed in a group
        auto found = std::find(alreadyPrinted.begin(), alreadyPrinted.end(), it.first);
        if (it.first.find(name) != std::string::npos && found == alreadyPrinted.end()) {
            // If the object has a string in its name and wasn't already printed, print it
            if (printNoGroups) {
                out << "no groups" << delim;
                printNoGroups = 0;
            }   
            out << it.second->getType() << delim;
            it.second->printValues(out);
        }
    }
}

void Manager::printGroup(std::string name, std::ostream &out) const {
    auto it = groups.find(name);
    
    if (it != groups.end()) {
        out << "group" << delim;
        it->second->printValues(out);
    } else {
        out << "Error: Group of name " << name << " not found";
    }
}
    
void Manager::play(std::string name) const {
    auto it = objects.find(name);

    if (it != objects.end()) {
        it->second->play();
    }
}

std::string Manager::removeMultimedia(std::string name) {
    std::string ret = "Removed object " + name;

    // Remove media object from the groups first
    for (const auto& i: groups) {
        i.second->erase(name);
    }
    // Remove the object itself
    if (objects.erase(name) == 0) {
        ret = "Error: Multimedia object of name " + name + " not found";
    }

    #ifdef DEBUG
    std::cout << "[D] Multimedia object of name " << name << " was removed\n";
    #endif

    return ret;
}

std::string Manager::removeGroup(std::string name) {
    std::string ret = "Removed group " + name;

    if (groups.erase(name) == 0) {
        ret = "Error: Group of name " + name + " not found";
    }

    #ifdef DEBUG
    std::cout << "[D] Group of name " << name << " was removed\n";
    #endif

    return ret;
}

std::shared_ptr<Multimedia> Manager::getObjectByName(std::string name) {
    auto it = objects.find(name);

    if (it != objects.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

std::shared_ptr<Group> Manager::getGroupByName(std::string name) {
    auto it = groups.find(name);

    if (it != groups.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}