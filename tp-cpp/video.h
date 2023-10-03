#ifndef VIDEO_H
#define VIDEO_H

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
    Video(std::string name, std::string filePath, int duration):
    Multimedia(name, filePath), duration(duration) {}

    /**
     * @brief Sends the name, file path and duration of video to output stream
     * 
     * @param out Stream to be outputted to
     */
    virtual void printValues(std::ostream &out) const override {
        out << "Name: " << getName() << ", Path: " << getFilePath() <<
        ", Duration: " << duration;
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
    void setDuration(int duration) {this->duration = duration;}
};

#endif