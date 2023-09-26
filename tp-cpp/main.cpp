#include <iostream>
#include <memory>
#include <list>
#include "multimedia.h"
#include "video.h"
#include "film.h"
#include "photo.h"
#include "group.h"

using namespace std;

typedef shared_ptr<Multimedia> MultimediaPtr;

int main(int argc, const char* argv[])
{
    int chap[5];
    for (int i = 1; i < 6; i++) chap[i] = i;

    shared_ptr<Film> f(new Film("avatar", "film.mov", 10, chap, 5));
    shared_ptr<Photo> p2(new Photo("gnu", "image2.png", 3.3, 7));
    
    Group g1("Group 1");
    g1.push_back(f);
    g1.push_back(make_shared<Video>("telecom", "video.mp4", 5));
    g1.push_back(make_shared<Photo>("github", "image1.png", 1.5, 4.1));
    g1.printValues(cout);

    Group g2("Group 2");
    g2.push_back(f);
    g2.push_back(p2);
    g2.printValues(cout);

    cout << "Finished succesfully\n";
    return 0;
}