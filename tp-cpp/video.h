#ifndef VIDEO_H
#define VIDEO_H

/**
 * @brief Class for a video object
 */
class Video : public Multimedia {
    private:
    int duration{};

    public:
    ~Video(){}
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
        ", Duration: " << duration << '\n';
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