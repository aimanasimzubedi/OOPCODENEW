#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "screens/Screen.hpp"

class Game {
public:
    Game(unsigned int w = 700, unsigned int h = 600, const std::string& title = "Piano Memory Challenge");
    ~Game();

    void run();

private:
    sf::RenderWindow window;
    Screen* current = nullptr;

    Screen* createScreen(ScreenID id);
    void processScreenSwitch();
};

#endif // GAME_HPP
