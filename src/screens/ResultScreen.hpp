#ifndef RESULTScreen_HPP
#define RESULTScreen_HPP

#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "..\core\Button.hpp"
#include <vector>
#include <string>

class ResultScreen : public Screen {
private:
    sf::Font font;
    sf::Text title;
    sf::Text scoreText;
    sf::Text accuracyText;
    sf::Text comboText;
    sf::Text timeText;

    Button backBtn;
    Button retryBtn;

    sf::RectangleShape gradient;
    std::vector<sf::CircleShape> particles;

    ScreenID goTo = NONE;

    // intiial result values
    int finalScore = 0;
    float finalAccuracy = 0.f;
    int maxCombo = 0;
    float finalTime = 0.f;

public:

    ResultScreen(int s, float a, int m, float t);
    ~ResultScreen() override = default;

    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;

    void setResults(int score, float accuracy, int combo, float time);

    ScreenID nextScreen() override;
    void resetNextScreen() override;
};

#endif // RESULTScreen_HPP
