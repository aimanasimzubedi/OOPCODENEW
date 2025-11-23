#ifndef MAINGAMESCREEN_HPP
#define MAINGAMESCREEN_HPP

#include "Screen.hpp"
#include "..\core\Button.hpp"
#include "..\piano\PianoSystem.hpp"
#include <vector>

class MainGameScreen : public Screen {
private:
    sf::Font font;
    sf::Text title;

    Button backBtn;
    sf::RectangleShape gradient;
    std::vector<sf::CircleShape> particles;

    ScreenID goTo = NONE;

    // Use Piano here too
    PianoSystem piano;

public:
    MainGameScreen();
    ~MainGameScreen() override = default;

    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;

    ScreenID nextScreen() override;
    void resetNextScreen() override;
};

#endif // MAINGAMESCREEN_HPP
