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
     * @return std::shared_ptr<Group> A pointer to the group created
     */
    std::shared_ptr<Group> createGroup(std::string name);

    /**
     * @brief Create a Photo object
     * 
     * @param name Name of the file
     * @param filePath Complete path of the file
     * @param lat Latitude of the photo
     * @param lon Longitude of the photo
     * @return std::shared_ptr<Photo> A pointer to the photo created
     */
    std::shared_ptr<Photo> createPhoto(std::string name, std::string filePath,
        float lat, float lon);
    
    /**
     * @brief Create a Video object
     * 
     * @param name Name of the file
     * @param filePath Complete path of the file
     * @param duration Duration of the video
     * @return std::shared_ptr<Video> A pointer to the video created
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
     * @return std::shared_ptr<Film> A pointer to the film created
     */
    std::shared_ptr<Film> createFilm(std::string name, std::string filePath,
        int duration, int* chapters, int numChapters);

    /**
     * @brief Prints the attributes of a multimedia object
     * 
     * @param name Name of the multimedia object
     * @param out Stream to be outputted to
     */
    void printMultimedia(std::string name, std::ostream &out) const;

    /**
     * @brief Prints the attributes of all multimedia objects of a given type
     * 
     * @param type Type of the multimedia object
     * @param out Stream to be outputted to
     */
    void printAll(std::string type, std::ostream &out) const;

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
    void removeMultimedia(std::string name);

    /**
     * @brief Removes a group from the manager
     * 
     * @param name Name of the group
     */
    void removeGroup(std::string name);

    /**
     * @brief Plays a multimedia object
     * 
     * @param name Name of the multimedia object
     */
    void play(std::string name) const;
};

#endif