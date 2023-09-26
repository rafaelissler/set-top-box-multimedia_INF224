#include <iostream>
#include "multimedia.h"
#include "video.h"
#include "film.h"
#include "photo.h"

using namespace std;

int main(int argc, const char* argv[])
{
    /*Video v("telecom", "video.mp4", 5);
    v.printNames(cout);
    v.setDuration(3);
    v.setName("video2");
    v.printNames(cout);

    Photo p("github", "image.png", 1.5, 4.1);
    p.printNames(cout);
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
        mediaArray[i]->printNames(cout);
        mediaArray[i]->play();
    }

    for (int i = 0; i < numArray; i++) {
        delete mediaArray[i];
    }*/

    /*Photo* p1 = new Photo("github", "image.png", 1.5, 4.1);
    Multimedia* m1 = p1;
    p1->printNames(cout);
    m1->printNames(cout);*/

    int chap[5];
    for (int i = 0; i < 5; i++) chap[i] = i;
    Film f("film", "video.mp4", 6, chap, 5);
    cout << f.getNumChapters() << '\n';
    f.printNames(cout);

    int* newchaps = f.getChapters();
    for (int i = 0; i < f.getNumChapters(); i++) cout << newchaps[i] << '\n';

    delete[] newchaps;

    cout << "Finished succesfully\n";
    return 0;
}
