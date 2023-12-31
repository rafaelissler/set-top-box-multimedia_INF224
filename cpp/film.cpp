#include <iostream>
#include <string>
#include "multimedia.h"
#include "video.h"
#include "film.h"

extern const char delim;

Film::~Film() {
    delete[] chapters;
    #ifdef DEBUG
    std::cout << "[D] Film " << Multimedia::getName() << " was deleted\n";
    #endif
}

Film::Film(): Video::Video(), chapters(NULL), numChapters(0) {}

Film::Film(std::string name, std::string filePath, const int duration,
const int* const chapters, const int numChapters):
    Video(name, filePath, duration) {
    this->numChapters = numChapters;
    this->chapters = new int[numChapters];
    for (int i = 0; i < numChapters; i++) {
        this->chapters[i] = chapters[i];
    }
}

void Film::printValues(std::ostream &out) const {
    Video::printValues(out);
    out << numChapters << delim;
    for (int i = 0; i < numChapters; i++) {
        out << chapters[i] << (i == (numChapters-1) ? delim : ' ');
    }
}

void Film::readValues(std::istream &in) {
    Video::readValues(in);

    std::string buf;
    getline(in, buf, delim);
    numChapters = std::stoi(buf);

    if (chapters) delete[] chapters;
    this->chapters = new int[numChapters];

    for (int i = 0; i < numChapters; i++) {
        in >> chapters[i];
    }
    in.get();       // Ignore last delimitation after the chapters
}

int* Film::getChapters() const {
    int* newChapters = new int[numChapters];
    for (int i = 0; i < numChapters; i++) {
        newChapters[i] = chapters[i];
    }
    return newChapters;
}

int Film::getNumChapters() const {return numChapters;}

void Film::setChapters(const int* const chapters, const int numChapters) {
    delete[] chapters;
    this->numChapters = numChapters;
    this->chapters = new int[numChapters];
    for (int i = 0; i < numChapters; i++) {
        this->chapters[i] = chapters[i];
    }
}

Film &Film::operator=(const Film &other) {
    Video::operator=(other);
    this->numChapters = other.numChapters;

    delete chapters;
    this->setChapters(other.chapters, other.numChapters);

    return *this;
}

Film::Film(const Film &other): Video(other) {
    this->numChapters = other.numChapters;
    this->setChapters(other.chapters, other.numChapters);
}

std::string Film::getType() const {return "film";}