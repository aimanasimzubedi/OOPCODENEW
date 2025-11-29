#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "screens/Screen.hpp"

class Game {
public:
    Game(unsigned int w = 700, unsigned int h = 600, const std::string& title = "Piano Memory Challenge");
    float finalTime=0.f;
    ~Game();

    void run();

private:
    sf::RenderWindow window;
    Screen* current = nullptr;

    // STORE RESULTS FOR RESULT SCREEN
    int score = 0;
    float accuracy = 0;
    int maxCombo = 0;

    Screen* createScreen(ScreenID id);
    void processScreenSwitch();
};

#endif // GAME_HPP
