#include <iostream>
#include "multimedia.h"
#include "video.h"
#include "photo.h"

using namespace std;

int main(int argc, const char* argv[])
{
    Video v("video2", "/mnt/d/academico/aulas/inf224/tp-cpp/video2.mp4", 5);
    v.printNames(cout);
    v.setDuration(3);
    v.setName("video2");
    v.printNames(cout);

    Photo p("demon", "/mnt/d/academico/aulas/inf224/tp-cpp/demon.png", 1.5, 4.1);
    p.printNames(cout);
    p.play();

    return 0;
}
