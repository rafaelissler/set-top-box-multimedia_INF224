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
    Multimedia(const std::string name, const std::string filePath);

    /**
     * @brief Sends the name and file path to output stream
     * 
     * @param out Stream to be outputted to
     */
    virtual void printValues(std::ostream &out) const;

    /**
     * @brief Retreives the name and file path from input stream
     * 
     * @param out Stream to be retreive from
     */
    virtual void readValues(std::istream &f);
    
    /**
     * @brief Executes the file
     */
    virtual void play() = 0;

    std::string getName() const;
    std::string getFilePath() const;
    virtual std::string getType() const = 0;

    void setName(const std::string name);
    void setFilePath(const std::string filePath);
};

#endif