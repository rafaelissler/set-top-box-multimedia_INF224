#ifndef VIDEO_H
#define VIDEO_H

extern const char delim;

/**
 * @brief Class for a video object
 */
class Video : public Multimedia {
    private:
    int duration{};

    public:
    ~Video() {
        #ifdef DEBUG
        std::cout << "[D] Video " << Multimedia::getName() << " was deleted\n";
        #endif
    }
    Video(): Multimedia() {}

    /**
     * @brief Construct a new Video object
     * 
     * @param name Name of the file
     * @param filePath Complete path of the file
     * @param duration Duration of the video
     */
    Video(std::string name, std::string filePath, const int duration):
    Multimedia(name, filePath), duration(duration) {}

    /**
     * @brief Sends the class variables to output stream
     * 
     * @param out Stream to be outputted to
     */
    void printValues(std::ostream &out) const override {
        Multimedia::printValues(out);
        out << duration << delim;
    }

    /**
     * @brief Retreives the class variables from input stream
     * 
     * @param out Stream to retreive values from
     */
    void readValues(std::istream &in) override {
        Multimedia::readValues(in);
        std::string buf;
        std::getline(in, buf, delim);
        duration = std::stoi(buf);
    }

    /**
     * @brief Executes the file
     */
    void play() override {
        std::string msg = "mpv " + getFilePath() + " &";

        if (system(msg.data()));    // Place in an if statement to ignore the warning message
    }

    std::string getType() const override {return "video";}

    int getDuration() const {return duration;}
    void setDuration(const int duration) {this->duration = duration;}
};

#endif