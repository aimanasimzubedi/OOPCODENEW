#pragma once
#include "Screen.hpp"
#include "../core/Button.hpp"
#include "../piano/PianoSystem.hpp"
#include <vector>
#include <string>

class GameModeScreen : public Screen {
private:
    sf::Font font;

    // UI elements
    Button goBtn;
    Button doneBtn;
    Button exitBtn;

    sf::Text sequenceText;
    sf::Text timerText;

    // Game state
    bool gameStarted = false;
    float elapsedTime = 0.0f;   // stopwatch (counts up)

    // Random sequence
    std::vector<std::string> noteSequence;

    // Piano
    PianoSystem piano;

    // Helper
    std::vector<std::string> generateSequence(int length);

public:
    int score = 0;
    int maxCombo = 0;
    float accuracy = 0;
    int correctPresses = 0;
    int totalPresses = 0;
    int combo = 0;

    int getScore() const { return score; }
    float getAccuracy() const { return accuracy; }
    int getMaxCombo() const { return maxCombo; }
    float getTime() const { return elapsedTime; }

    GameModeScreen();
    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
    ScreenID nextScreen() override;
    void resetNextScreen() override;
};
