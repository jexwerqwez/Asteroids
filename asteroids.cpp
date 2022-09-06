#include "asteroids.h"

char Spaceship::draw_spaceship(int signal) {
    if (signal == 1) {
        return '>';
    } else if (signal == 2) {
        return '<';
    } else if (signal == 3) {
        return '^';
    } else if (signal == 4) {
        return 'v';
    } else {
        return '>';
    }
}