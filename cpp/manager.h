#ifndef MANAGER_H
#define MANAGER_H

/**
 * @brief Class for the manager object
 */
class Manager {
    private:
    std::map<std::string, std::shared_ptr<Multimedia>> objects;
    std::map<std::string, std::shared_ptr<Group>> groups;

    public:
    ~Manager();
    Manager();

    /**
     * @brief Create a group
     * 
     * @param name Name of the group
     * @return Returns a pointer to the group std::shared_ptr<Group> if the operation was
     * succesfull or nullptr if a group with the same name already exists
     */
    std::shared_ptr<Group> createGroup(std::string name);

    /**
     * @brief Create a Photo object
     * 
     * @param name Name of the file
     * @param filePath Complete path of the file
     * @param lat Latitude of the photo
     * @param lon Longitude of the photo
     * @return Return a pointer to the Photo created std::shared_ptr<Photo> if the operation
     * was succesfull or an empty Photo if an object with same name already exists
     */
    std::shared_ptr<Photo> createPhoto(std::string name, std::string filePath,
        float lat, float lon);
    
    /**
     * @brief Create a Video object
     * 
     * @param name Name of the file
     * @param filePath Complete path of the file
     * @param duration Duration of the video
     * @return Return a pointer to the Video created std::shared_ptr<Photo> if the operation
     * was succesfull or an empty Video if an object with same name already exists
     */
    std::shared_ptr<Video> createVideo(std::string name, std::string filePath,
        int duration);
    
    /**
     * @brief Create a Film object
     * 
     * @param name Name of the file
     * @param filePath Complete path of the file
     * @param duration Duration of the video
     * @param chapters Pointer to table that contains the chapter durations
     * @param numChapters Number of chapters
     * @return Return a pointer to the Film created std::shared_ptr<Photo> if the operation
     * was succesfull or an empty Film if an object with same name already exists
     */
    std::shared_ptr<Film> createFilm(std::string name, std::string filePath,
        int duration, int* chapters, int numChapters);

    /**
     * @brief Factory that creates a multimedia object based on the class name
     * 
     * @param nameType Name of the class to create (e.g.: photo, video, film)
     * @param name Name of the object
     * @return Return a pointer to the Multimedia object created std::shared_ptr<Multimedia>
     * if the operation was succesfull or an empty Multimedia if an object with same name already exists
     * or nullptr if the nameType was unknown
     */
    std::shared_ptr<Multimedia> createMultimedia(std::string nameType, std::string name);

    /**
     * @brief Reads from an input stream and stores the objects
     * 
     * @param in Stream to read from
     */
    void readFromFile(std::istream &in);

    /**
     * @brief Prints the attributes of a multimedia object
     * 
     * @param name Name of the multimedia object
     * @param out Stream to be outputted to
     */
    void printMultimedia(std::string name, std::ostream &out) const;

    /**
     * @brief Prints the attributes of all multimedia objects and groups
     * 
     * @param out Stream to be outputted to
     */
    void printAllMultimedia(std::ostream &out) const;

    /**
     * @brief Prints the attributes of all multimedia objects of a given type
     * 
     * @param type Type of the multimedia object
     * @param out Stream to be outputted to
     */
    void printType(std::string type, std::ostream &out) const;

    /**
     * @brief Prints the attributes of all multimedia objects or groups that
     * contains a given string in their name
     * 
     * @param name Name used to search for the objects
     * @param out Stream to be outputted to
     */
    void printContains(std::string name, std::ostream &out) const;

    /**
     * @brief Prints the attributes and multimedia objects of a group
     * 
     * @param name Name of the group
     * @param out Stream to be outputted to
     */
    void printGroup(std::string name, std::ostream &out) const;

    /**
     * @brief Removes a multimedia object from the manager
     * 
     * @param name Name of the multimedia object
     */
    std::string removeMultimedia(std::string name);

    /**
     * @brief Removes a group from the manager
     * 
     * @param name Name of the group
     */
    std::string removeGroup(std::string name);

    /**
     * @brief Plays a multimedia object
     * 
     * @param name Name of the multimedia object
     */
    void play(std::string name) const;

    /**
     * @brief Get the object by its name
     * 
     * @param name Name of the object
     * @return Returns the object std::shared_ptr<Multimedia> if the operation was succesful
     * or nullptr if an object wasn't found
     */
    std::shared_ptr<Multimedia> getObjectByName(std::string name);

    /**
     * @brief Get the group by its name
     * 
     * @param name Name of the group
     * @return Returns the group std::shared_ptr<Group> if the operation was succesful or
     * nullptr if a group wasn't found
     */
    std::shared_ptr<Group> getGroupByName(std::string name);
};

#endif