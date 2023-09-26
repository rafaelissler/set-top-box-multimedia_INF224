#include <iostream>
#include <string>
#include <memory>
#include <list>
#include "multimedia.h"
#include "group.h"

Group::Group(std::string name): std::list<std::shared_ptr<Multimedia>>(), name(name) {}

void Group::printValues(std::ostream &out) const {
    out << "Group name: " << name << '\n';
    for (const auto& i: *this) {
        out << "\t>";
        i->printValues(out);
    }
}

void Group::erase(std::string name) {
    for (auto it = this->begin(); it !=this->end();) {
        if ((*it)->getName() == name) {
            std::list<std::shared_ptr<Multimedia>>::erase(it);
            break;
        } else {++it;}
    }
}

std::string Group::getName() const {return name;}
void Group::setName(std::string name) {this->name = name;}