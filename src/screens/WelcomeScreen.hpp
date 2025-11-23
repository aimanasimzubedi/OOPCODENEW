#ifndef WELCOMESCREEN_HPP
#define WELCOMESCREEN_HPP

#include "Screen.hpp"
#include "../core/Button.hpp"
#include <SFML/Audio.hpp>
#include <vector>

class WelcomeScreen : public Screen {
private:
    sf::Font font;
    sf::Text title;

    Button startBtn;
    Button freeBtn;
    Button exitBtn;

    sf::RectangleShape gradient;
    std::vector<sf::CircleShape> particles;
    float glowTimer = 0;
    sf::Music bgMusic;
    ScreenID next = NONE;

public:
    WelcomeScreen();
    ~WelcomeScreen() override = default;

    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;

    ScreenID nextScreen() override;
    void resetNextScreen() override;
};

#endif // WELCOMESCREEN_HPP
