#ifndef FILM_H
#define FILM_H

/**
 * @brief Class for a Film object
 */
class Film : public Video {
    private:
    int* chapters;
    int numChapters;

    public:
    ~Film();
    Film();

    /**
     * @brief Construct a new Film object
     * 
     * @param name Name of the file
     * @param filePath Complete path of the file
     * @param duration Duration of the video
     * @param chapters Pointer to table that contains the chapter durations
     * @param numChapters Number of chapters
     */
    Film(std::string name, std::string filePath, int duration, int* chapters, int numChapters);

    /**
     * @brief Sends the name, file path, duration, chapter durations
     * and number of chapters to output stream
     * 
     * @param out Stream to be outputted to
     */
    void printValues(std::ostream &out) const override;

    /**
     * @brief Get the Film's chapter durations
     * 
     * @return Returns copy of table of chapter durations. Must delete after use
     */
    int* getChapters() const;
    int getNumChapters() const;
    std::string getType() const override;

    void setChapters(int* chapters, int numChapters);
};

#endif