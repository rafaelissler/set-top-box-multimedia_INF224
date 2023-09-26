#ifndef FILM_H
#define FILM_H


class Film : public Video {
    private:
    int* chapters;
    int numChapters;

    public:
    ~Film();
    Film();
    Film(std::string name, std::string filePath, int duration, int* chapters, int numChapters);

    void printNames(std::ostream &out) const override;

    int* getChapters() const;
    int getNumChapters() const;

    void setChapters(int* chapters, int numChapters);
};

#endif