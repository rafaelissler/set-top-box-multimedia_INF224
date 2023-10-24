#include "main.h"

using namespace std;

int main(int argc, const char* argv[]) {
    // Initialize everything
    startupCmds();
    Manager mngr;

    int chapters1[5];
    int chapters2[7];
    for (int i = 0; i < 5; i++) chapters1[i] = i+1;
    for (int i = 6; i >= 0; i--) chapters2[i] = i+10;
    shared_ptr<Film> f1 = mngr.createFilm("avatar", "film.mov", 10, chapters1, 5);
    shared_ptr<Film> f2 = mngr.createFilm("barbie", "barbie.mov", 5, chapters2, 7);
    shared_ptr<Photo> p1 = mngr.createPhoto("github", "photo1.png", 3.3, 7);
    shared_ptr<Photo> p2 = mngr.createPhoto("gnu", "photo2.png", 3.7, 4);
    shared_ptr<Video> v1 = mngr.createVideo("telecom", "video.mp4", 5);
    shared_ptr<Video> v2 = mngr.createVideo("gitlab", "video2.mp4", 7);

    shared_ptr<Group> group = mngr.createGroup("toto");
    group->push_back(f1);
    group->push_back(p1);
    group->push_back(v1);

    shared_ptr<Group> group2 = mngr.createGroup("titi");
    group2->push_back(f1);
    group2->push_back(f2);
    group2->push_back(p2);
    group2->push_back(v2);

    std::ofstream file("_print.txt");
    if (!file) return 1;
    mngr.printAllMultimedia(file);
    file.close();

    /*std::ifstream file2("movie.txt");
    if (!file) return 1;
    Film newf;
    newf.readValues(file2);
    newf.printValues(std::cout);
    newf.readValues(file2);
    newf.printValues(std::cout);
    file2.close();
    mngr.printContains("t",std::cout);*/
    cout << "Finished succesfully\n";
    return 0;
}