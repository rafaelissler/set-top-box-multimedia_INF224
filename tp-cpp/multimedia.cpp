#include <iostream>
#include <string>
#include "multimedia.h"

Multimedia::Multimedia() {
    this->name = "";
    this->filePath = "";
}

Multimedia::Multimedia(std::string name, std::string filePath) {
    this->name = name;
    this->filePath = filePath;
}

Multimedia::~Multimedia() {}

void Multimedia::printNames(std::ostream &out) const {
    out << filePath << "/" << name << '\n';
}

std::string Multimedia::getName() const { return name; }
std::string Multimedia::getFilePath() const { return filePath; }
void Multimedia::setName(std::string name) { this->name = name; }
void Multimedia::setFilePath(std::string filePath) { this->filePath = filePath; }