#include <iostream>
#include <memory>
#include <map>
#include "multimedia.h"
#include "video.h"
#include "film.h"
#include "photo.h"
#include "group.h"
#include "manager.h"

Manager::~Manager() {}
Manager::Manager() {}

std::shared_ptr<Group> Manager::createGroup(std::string name) {
    groups.emplace(name, std::make_shared<Group>(name));
    return groups[name];
}

std::shared_ptr<Photo> Manager::createPhoto(std::string name, std::string filePath,
float lat, float lon) {
    std::shared_ptr<Photo> obj = std::make_shared<Photo>(name, filePath, lat, lon);
    objects.emplace(name, obj);
    return obj;
}

std::shared_ptr<Video> Manager::createVideo(std::string name, std::string filePath,
int duration) {
    std::shared_ptr<Video> obj = std::make_shared<Video>(name, filePath, duration);
    objects.emplace(name, obj);
    return obj;
}

std::shared_ptr<Film> Manager::createFilm(std::string name, std::string filePath,
int duration, int* chapters, int numChapters) {
    std::shared_ptr<Film> obj = std::make_shared<Film>(name, filePath, duration, chapters, numChapters);
    objects.emplace(name, obj);
    return obj;
}

void Manager::printMultimedia(std::string name, std::ostream &out) const {
    auto it = objects.find(name);

    if (it != objects.end()) {
        out << it->second->getType() << '\n';
        it->second->printValues(out);
    } else {
        out << "Error: Multimedia object of name " << name << " not found";
        #ifdef DEBUG
        std::cout << "[D] Error: Multimedia object of name " << name << " not found\n";
        #endif
    }
}

void Manager::printAllMultimedia(std::ostream &out) const {
    for (const auto& it : objects) {
        out << it.second->getType() << '\n';
        it.second->printValues(out);
    }
}

void Manager::printType(std::string type, std::ostream &out) const {
    // Iterate through media objects and print the ones with the given type
    for (const auto& it : objects) {
        if (it.second->getType() == type) {
            out << it.second->getType() << '\n';
            it.second->printValues(out);
        }
    }
}

void Manager::printContains(std::string name, std::ostream &out) const {
    // Print the groups with the name (including their objects)
    for (const auto& it : groups) {
        if (it.first.find(name) != std::string::npos) {
            out << "group\n";
            it.second->printValues(out);
        }
    }
    // Search through the multimedia objects
    for (const auto& it : objects) {
        if (it.first.find(name) != std::string::npos) {
            out << it.second->getType() << '\n';
            it.second->printValues(out);
        }
    }
}

void Manager::printGroup(std::string name, std::ostream &out) const {
    auto it = groups.find(name);
    
    if (it != groups.end()) {
        out << "group\n";
        it->second->printValues(out);
    } else {
        out << "Error: Group of name " << name << " not found";
        #ifdef DEBUG
        std::cout << "[D] Error: Group of name " << name << " not found\n";
        #endif
    }
}
    
void Manager::play(std::string name) const {
    auto it = objects.find(name);

    if (it != objects.end()) {
        it->second->play();
    } else {
        #ifdef DEBUG
        std::cout << "[D] Error: Multimedia object of name " << name << " not found\n";
        #endif
    }
}

void Manager::removeMultimedia(std::string name) {
    // Remove media object from the groups first
    for (const auto& i: groups) {
        i.second->erase(name);
    }
    // Remove the object itself
    if (objects.erase(name) == 0) {
        std::cout << "Error: Multimedia object of name " << name << " not found\n";
    }

    #ifdef DEBUG
    std::cout << "[D] Multimedia object of name " << name << " was removed\n";
    #endif
}

void Manager::removeGroup(std::string name) {
    if (groups.erase(name) == 0) {
        std::cout << "Error: Group of name " << name << " not found\n";
    }

    #ifdef DEBUG
    std::cout << "[D] Group of name " << name << " was removed\n";
    #endif
}

std::shared_ptr<Multimedia> createMultimedia(std::string name);