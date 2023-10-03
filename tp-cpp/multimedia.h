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
    virtual ~Multimedia();
    Multimedia();
    /**
     * @brief Construct a new Multimedia object
     * 
     * @param name Name of the file
     * @param filePath Complete path of the file
     */
    Multimedia(std::string name, std::string filePath);

    /**
     * @brief Sends the name and file path to output stream
     * 
     * @param out Stream to be outputted to
     */
    virtual void printValues(std::ostream &out) const;
    
    /**
     * @brief Executes the file
     */
    void virtual play() = 0;

    std::string getName() const;
    std::string getFilePath() const;
    virtual std::string getType() const = 0;

    void setName(std::string name);
    void setFilePath(std::string filePath);
};

#endif