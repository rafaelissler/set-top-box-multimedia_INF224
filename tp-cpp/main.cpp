#include <iostream>
#include "multimedia.h"
#include "video.h"
#include "film.h"
#include "photo.h"
#include "group.h"

using namespace std;

int main(int argc, const char* argv[])
{
    /*Video v("telecom", "video.mp4", 5);
    v.printValues(cout);
    v.setDuration(3);
    v.setName("video2");
    v.printValues(cout);

    Photo p("github", "image.png", 1.5, 4.1);
    p.printValues(cout);
    p.play();*/

    /*const int numArray = 5;
    Multimedia* mediaArray[numArray];
    string name = "";
    int j = 1, k = 1;

    for (int i = 0; i < numArray; i++) {
        if (i % 2) {
            name = "photo" + to_string(j++);
            mediaArray[i] = new Photo(name, name + ".png", (float)i+1.5, (float)i+1.3);
        } else {
            name = "video" + to_string(k++);
            mediaArray[i] = new Video(name, name + ".mp4", i);
        }
    }

    for (int i = 0; i < numArray; i++) {
        mediaArray[i]->printValues(cout);
        mediaArray[i]->play();
    }

    for (int i = 0; i < numArray; i++) {
        delete mediaArray[i];
    }*/

    /*Photo* p1 = new Photo("github", "image.png", 1.5, 4.1);
    Multimedia* m1 = p1;
    p1->printValues(cout);
    m1->printValues(cout);*/

    int chap[5];
    for (int i = 1; i < 6; i++) chap[i] = i;
    Film f("avatar", "film.mov", 10, chap, 5);
    /*cout << f.getNumChapters() << '\n';
    f.printValues(cout);

    int* newchaps = f.getChapters();
    for (int i = 0; i < f.getNumChapters(); i++) cout << newchaps[i] << '\n';

    delete[] newchaps;*/

    Video v("telecom", "video.mp4", 5);
    Photo p1("github", "image1.png", 1.5, 4.1);
    Photo p2("gnu", "image2.png", 3.3, 7);

    Group g1("Group 1");
    g1.push_back(&f);
    g1.push_back(&v);
    g1.push_back(&p1);
    g1.printValues(cout);

    Group g2("Group 2");
    g2.push_back(&f);
    g2.push_back(&p2);
    g2.printValues(cout);

    cout << "Finished succesfully\n";
    return 0;
}
