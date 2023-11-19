#ifndef PHOTO_H
#define PHOTO_H

extern const char delim;

/**
 * @brief Class for a photo object
 */
class Photo : public Multimedia {
    private:
    float lat{}, lon{};

    public:
    ~Photo() {
        #ifdef DEBUG
        std::cout << "[D] Photo " << Multimedia::getName() << " was deleted\n";
        #endif
    }
    Photo(): Multimedia() {}

    /**
     * @brief Construct a new Photo object
     * 
     * @param name Name of the file
     * @param filePath Complete path of the file
     * @param lat Latitude of the photo
     * @param lon Longitude of the photo
     */
    Photo(std::string name, std::string filePath, const float lat, const float lon):
    Multimedia(name, filePath), lat(lat), lon(lon) {}

    /**
     * @brief Sends the class variables to output stream
     * 
     * @param out Stream to be outputted to
     */
    void printValues(std::ostream &out) const override {
        Multimedia::printValues(out);
        out << lat << delim << lon << delim;
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
        lat = std::stof(buf);
        std::getline(in, buf, delim);
        lon = std::stof(buf);
    }

    /**
     * @brief Executes the file
     */
    void play() override {
        std::string msg = "imagej " + getFilePath() + " &";
        if (system(msg.data()));    // Place in an if statement to ignore the warning message
    }

    std::string getType() const override {return "photo";}

    float getLat() const {return lat;}
    float getLon() const {return lon;}
    void setLat(const float lat) {this->lat = lat;}
    void setLon(const float lon) {this->lon = lon;}
};

#endif