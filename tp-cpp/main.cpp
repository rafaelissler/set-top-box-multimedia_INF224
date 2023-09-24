#include <iostream>
#include "multimedia.h"

using namespace std;

int main(int argc, const char* argv[])
{
    Multimedia a("abc", "c:/usr/videos");
    a.printNames(std::cout);
    return 0;
}
