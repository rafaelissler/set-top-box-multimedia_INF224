#include <iostream>
#include <string>
#include <memory>
#include <list>
#include "multimedia.h"
#include "group.h"

extern const char delim;

Group::Group(std::string name): std::list<std::shared_ptr<Multimedia>>(), name(name) {}

void Group::printValues(std::ostream &out) const {
    // Print first the name of the group, then all of it's objects contents
    out << name << delim;
    for (const auto& i: *this) {
        out << i->getType() << delim;
        i->printValues(out);
    }
}

void Group::erase(std::string name) {
    // Iterate through the groups
    for (auto it = this->begin(); it !=this->end();) {
        // If it has the give name, delete it
        if ((*it)->getName() == name) {
            std::list<std::shared_ptr<Multimedia>>::erase(it);
            break;
        } else {++it;}
    }
}

std::string Group::getName() const {return name;}
void Group::setName(std::string name) {this->name = name;}