#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

class Multimedia {
    private:
    std::string name;
    std::string filePath;

    public:
    Multimedia();
    Multimedia(std::string name, std::string filePath);
    ~Multimedia();

    void printNames(std::ostream &out) const;

    std::string getName() const;
    std::string getFilePath() const;

    void setName(std::string name);
    void setFilePath(std::string filePath);
};

#endif