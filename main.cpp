#include "asteroids.h"
using namespace std;

int main (int argc, char* argv[]) {
    Settings setts;
    string filename = argv[1];
    Game game(filename);
    game.menu();
    return 0;
}
