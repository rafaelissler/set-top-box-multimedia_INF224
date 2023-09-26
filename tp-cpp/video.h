#ifndef VIDEO_H
#define VIDEO_H

/**
 * @brief Class for a photo object
 */
class Video : public Multimedia {
    private:
    int duration{};

    public:
    ~Video(){}
    Video(): Multimedia() {}
    Video(std::string name, std::string filePath, int duration):
    Multimedia(name, filePath), duration(duration) {}

    /**
     * @brief Sends the name and file path to output stream
     * 
     * @param out Stream to be outputted to
     */
    void printNames(std::ostream &out) const override {
        out << getName() << ", " << getFilePath() << ", " << duration << '\n';
    }

    /**
     * @brief Executes the file
     */
    void play() override {
        std::string msg = "mpv " + getFilePath() + " &";
        system(msg.data());
    }

    int getDuration() const {return duration;}
    void setDuration(int duration) {this->duration = duration;}
};

#endif