#ifndef MANAGER_H
#define MANAGER_H

class Manager {
    private:
    std::map<std::string, std::shared_ptr<Multimedia>> objects;
    std::map<std::string, std::shared_ptr<Group>> groups;

    public:
    ~Manager();
    Manager();

    std::shared_ptr<Group> createGroup(std::string name);
    std::shared_ptr<Photo> createPhoto(std::string name, std::string filePath,
        float lat, float lon);
    std::shared_ptr<Video> createVideo(std::string name, std::string filePath,
        int duration);
    std::shared_ptr<Film> createFilm(std::string name, std::string filePath,
        int duration, int* chapters, int numChapters);

    void printMultimedia(std::string name, std::ostream &out) const;
    void printGroup(std::string name, std::ostream &out) const;
    void removeMultimedia(std::string name);
    void removeGroup(std::string name);
    void play(std::string name) const;
};

#endif