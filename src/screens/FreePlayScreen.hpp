#ifndef FREEPLAYScreen_HPP
#define FREEPLAYScreen_HPP

#include "Screen.hpp"
#include "..\core\Button.hpp"
#include "../piano\PianoSystem.hpp"
#include <vector>

class FreePlayScreen : public Screen {
private:
    sf::Font font;
    sf::Text title;

    Button backBtn;
    sf::RectangleShape gradient;
    std::vector<sf::CircleShape> particles;

    ScreenID goTo = NONE;

    // replaced raw key vectors with Piano instance
    PianoSystem piano;

public:
    FreePlayScreen();
    ~FreePlayScreen() override = default;

    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;

    ScreenID nextScreen() override;
    void resetNextScreen() override;
};

#endif // FREEPLAYScreen_HPP
