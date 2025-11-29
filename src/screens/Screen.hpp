#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>

class Game; // forward declaration
enum ScreenID {
    NONE,
    WELCOME,
    FREEPLAY,
    MAINGAME,
    GAMEMODE,
    RESULT
};

class Screen {
protected:
    ScreenID goTo = NONE;
public:
    virtual ~Screen() {}
    virtual void handleEvents(sf::RenderWindow& window) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ScreenID nextScreen() { return NONE; }
    virtual void resetNextScreen() {}
};

#endif // SCREEN_HPP
