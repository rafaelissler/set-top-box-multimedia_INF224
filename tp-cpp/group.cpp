#include <iostream>
#include <string>
#include "multimedia.h"
#include "group.h"

Group::Group(std::string name): std::list<Multimedia*>(), name(name) {}

void Group::printValues(std::ostream &out) {
    out << "Group name: " << name << '\n';
    for (auto const& i: *this) {
        i->printValues(out);
    }
    out << "_______________________________________________\n";
}

std::string Group::getName() const {return name;}
void Group::setName(std::string name) {this->name = name;}