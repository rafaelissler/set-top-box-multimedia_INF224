#include <iostream>
#include <string>
#include "multimedia.h"
#include "video.h"
#include "film.h"

Film::~Film() {
    delete[] chapters;
}

Film::Film(): Video::Video(), chapters(NULL), numChapters(0) {}

Film::Film(std::string name, std::string filePath, int duration, int* chapters, int numChapters):
    Video(name, filePath, duration) {
    this->numChapters = numChapters;
    this->chapters = new int[numChapters];
    for (int i = 0; i < numChapters; i++) {
        this->chapters[i] = chapters[i];
    }
}

void Film::printValues(std::ostream &out) const {
        out << "Name: " << getName() << ", Path: " << getFilePath() <<
        ", Duration: " << getDuration() << ", Chapters: {";
        for (int i = 0; i < numChapters; i++) {
            out << chapters[i];
            if (i < (numChapters-1)) out << ", ";
        }
        out << "}\n";
}

int* Film::getChapters() const {
    int* newChapters = new int[numChapters];
    for (int i = 0; i < numChapters; i++) {
        newChapters[i] = chapters[i];
    }
    return newChapters;
}

int Film::getNumChapters() const {return numChapters;}

void Film::setChapters(int* chapters, int numChapters) {
    delete[] chapters;
    this->numChapters = numChapters;
    this->chapters = new int[numChapters];
    for (int i = 0; i < numChapters; i++) {
        this->chapters[i] = chapters[i];
    }
}