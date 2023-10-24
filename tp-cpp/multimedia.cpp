#include <iostream>
#include <string>
#include "multimedia.h"

Multimedia::Multimedia() {
    this->name = "";
    this->filePath = "";
}

Multimedia::Multimedia(const std::string name, const std::string filePath) {
    this->name = name;
    this->filePath = filePath;
}

Multimedia::~Multimedia() {}

void Multimedia::printValues(std::ostream &out) const {
    out << name << '\n' << filePath << '\n';
}

void Multimedia::readValues(std::istream &in) {
    getline(in, name);
    std::cout << "Name: " << name << '\n';
    getline(in, filePath);
    std::cout << "Filepath: " << filePath << '\n';
}

std::string Multimedia::getName() const { return name; }
std::string Multimedia::getFilePath() const { return filePath; }
void Multimedia::setName(const std::string name) { this->name = name; }
void Multimedia::setFilePath(const std::string filePath) { this->filePath = filePath; }