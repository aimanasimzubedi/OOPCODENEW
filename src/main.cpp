#include "game.hpp"

int main() {
    Game game(700, 600, "Piano Memory Challenge");
    game.run();
    return 0;
}
//g++ src/*.cpp src/screens/*.cpp src/core/*.cpp src/piano/*.cpp ^-I./src -I./src/screens -I./src/core -I./src/piano ^-o PianoGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
