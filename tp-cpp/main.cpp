#include "main.h"

using namespace std;

const int PORT = 4466;

int main(int argc, const char* argv[]) {
    // Initialize everything
    startupCmds();
    Manager mngr;

    int chapters[5];
    for (int i = 0; i < 5; i++) chapters[i] = i+1;
    shared_ptr<Film> f = mngr.createFilm("avatar", "film.mov", 10, chapters, 5);
    shared_ptr<Photo> p1 = mngr.createPhoto("github", "photo1.png", 3.3, 7);
    shared_ptr<Photo> p2 = mngr.createPhoto("gnu", "photo2.png", 3.7, 4);
    shared_ptr<Video> v1 = mngr.createVideo("telecom", "video.mp4", 5);
    shared_ptr<Video> v2 = mngr.createVideo("gitlab", "video2.mp4", 7);

    shared_ptr<Group> group = mngr.createGroup("toto");
    group->push_back(f);
    group->push_back(p1);
    group->push_back(v1);

    shared_ptr<Group> group2 = mngr.createGroup("titi");
    group2->push_back(f);
    group2->push_back(p2);
    group2->push_back(v2);

    // Define the callback of server
    shared_ptr<TCPServer> server = make_shared<TCPServer>([&]
    (std::string const& request, std::string& response) {
        #ifdef DEBUG
        cout << "[D] Request received: " << request << endl;
        #endif
        // Default response
        response = "OK";

        stringstream ss(request);
        string arg;
        ss >> arg;  // Get first argument

        // If it failed or client wants to quit, disconnect
        if (!ss.fail() && arg != "quit") {
            auto it = cmds.find(arg);
            if (it != cmds.end()) {
                // If it finds the request
                if (!ss.fail()) {
                    // Call the lambda associated with request
                    response = it->second(ss, mngr);
                    #ifdef DEBUG
                    std::cout << "[D] What will be sent: " << response << '\n';
                    #endif
                }
            } else {
                response = "Error: Could not understand " + arg;
                std::cout << response << '\n';
            }
        }
        else {
            response = "ERROR";
        }
        ss.str("");

        return true;
    });

    cout << "Opening server on port " << PORT << '\n';
    int err = server->run(PORT);
    if (err < 0) {
        cout << "Error: Server could not be started\n";
        return 1;
    }

    cout << "Finished succesfully\n";
    return 0;
}