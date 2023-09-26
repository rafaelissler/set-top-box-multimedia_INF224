#include <iostream>
#include <memory>
#include <map>
#include "multimedia.h"
#include "video.h"
#include "film.h"
#include "photo.h"
#include "group.h"
#include "manager.h"

using namespace std;

typedef shared_ptr<Multimedia> MultimediaPtr;

int main(int argc, const char* argv[])
{
    int chap[5];
    for (int i = 0; i < 5; i++) chap[i] = i+1;

    Manager mngr;
    
    shared_ptr<Film> f = mngr.createFilm("avatar", "film.mov", 10, chap, 5);
    f->printValues(cout);
    
    shared_ptr<Photo> p = mngr.createPhoto("gnu", "image.png", 3.3, 7);
    p->printValues(cout);

    shared_ptr<Video> v = mngr.createVideo("telecom", "video.mp4", 5);
    v->printValues(cout);

    shared_ptr<Group> group = mngr.createGroup("Group 1");
    group->push_back(f);
    group->push_back(p);
    group->push_back(v);
    group->printValues(cout);

    cout << "_______________________________________\n";

    mngr.printMultimedia("avatar", cout);
    mngr.printMultimedia("gnu", cout);
    mngr.printMultimedia("telecom", cout);
    mngr.printGroup("Group 1", cout);

    mngr.printMultimedia("abc", cout);
    mngr.printGroup("Group 2", cout);

    cout << "_______________________________________\n";
    mngr.removeMultimedia("gnu");
    mngr.printGroup("Group 1", cout);
    mngr.removeMultimedia("gnu");

    mngr.removeGroup("Group 1");
    mngr.printGroup("Group 1", cout);
    mngr.printMultimedia("avatar", cout);
    mngr.printMultimedia("telecom", cout);

    /*shared_ptr<Film> f(new Film("avatar", "film.mov", 10, chap, 5));
    shared_ptr<Photo> p2(new Photo("gnu", "image2.png", 3.3, 7));
    
    Group g1("Group 1");
    g1.push_back(f);
    g1.push_back(make_shared<Video>("telecom", "video.mp4", 5));
    g1.push_back(make_shared<Photo>("github", "image1.png", 1.5, 4.1));
    g1.printValues(cout);

    Group g2("Group 2");
    g2.push_back(f);
    g2.push_back(p2);
    g2.printValues(cout);*/

    cout << "Finished succesfully\n";
    return 0;
}