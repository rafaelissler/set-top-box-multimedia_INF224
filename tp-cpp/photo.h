#ifndef PHOTO_H
#define PHOTO_H

/**
 * @brief Class for a video object
 */
class Photo : public Multimedia {
    private:
    float lat{}, lon{};

    public:
    ~Photo() {}
    Photo(): Multimedia() {}
    Photo(std::string name, std::string filePath, float lat, float lon):
    Multimedia(name, filePath), lat(lat), lon(lon) {}

    /**
     * @brief Sends the name and file path to output stream
     * 
     * @param out Stream to be outputted to
     */
    void printNames(std::ostream &out) const override {
        out << "Name:" << getName() << ", Path:" << getFilePath() <<
        ", Latitude:"  << lat << ", Longitude" << lon << '\n';
    }

    /**
     * @brief Executes the file
     */
    void play() override {
        std::string msg = "imagej " + getFilePath() + " &";
        system(msg.data());
    }

    float getLat() const {return lat;}
    float getLon() const {return lon;}
    void setLat(float lat) {this->lat = lat;}
    void setLon(float lon) {this->lon = lon;}
};

#endif