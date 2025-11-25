#ifndef RESULTScreen_HPP
#define RESULTScreen_HPP

#include "Screen.hpp"
#include "..\core\Button.hpp"
#include <vector>

class ResultScreen : public Screen {
private:
    sf::Font font;
    sf::Text title;
    sf::Text scoreText;
    sf::Text accuracyText;
    sf::Text comboText;

    Button backBtn;
    Button retryBtn;

    sf::RectangleShape gradient;
    std::vector<sf::CircleShape> particles;

    ScreenID goTo = NONE;

    // Cached values from game results
    int finalScore = 0;
    float finalAccuracy = 0.f;
    int maxCombo = 0;

public:
    ResultScreen(int score, float accuracy, int combo);
    ~ResultScreen() override = default;

    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;

    ScreenID nextScreen() override;
    void resetNextScreen() override;
};

#endif // RESULTScreen_HPP
