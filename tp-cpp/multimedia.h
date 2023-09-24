#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

/**
 * @brief Multimedia class used as a base
 */
class Multimedia {
    private:
    std::string name;
    std::string filePath;

    public:
    ~Multimedia();
    Multimedia();
    /**
     * @brief Construct a new Multimedia object
     * 
     * @param name Name of the file
     * @param filePath Complete path of the file
     */
    Multimedia(std::string name, std::string filePath);

    /**
     * @brief Sends the name and file path to output stream in the
     * format [filePath]/[name]
     * 
     * @param out Stream to be outputted to
     */
    void printNames(std::ostream &out) const;

    std::string getName() const;
    std::string getFilePath() const;

    void setName(std::string name);
    void setFilePath(std::string filePath);
};

#endif