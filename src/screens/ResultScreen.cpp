#include "ResultScreen.hpp"

ResultScreen::ResultScreen(int score, float accuracy, int combo)
    : finalScore(score), finalAccuracy(accuracy), maxCombo(combo)
{
    // FONT + TITLE
    font.loadFromFile("src/resources/fonts/ARIAL.TTF");

    title.setFont(font);
    title.setString("Results");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);

    sf::FloatRect tb = title.getLocalBounds();
    title.setOrigin(tb.width / 2, tb.height / 2);
    title.setPosition(350.f, 70.f);

    // RESULT TEXTS
    scoreText.setFont(font);
    scoreText.setCharacterSize(32);
    scoreText.setFillColor(sf::Color(230, 230, 255));
    scoreText.setString("Score: " + std::to_string(finalScore));
    scoreText.setPosition(200.f, 170.f);

    accuracyText.setFont(font);
    accuracyText.setCharacterSize(32);
    accuracyText.setFillColor(sf::Color(230, 230, 255));
    accuracyText.setString("Accuracy: " + std::to_string((int)finalAccuracy) + "%");
    accuracyText.setPosition(200.f, 230.f);

    comboText.setFont(font);
    comboText.setCharacterSize(32);
    comboText.setFillColor(sf::Color(230, 230, 255));
    comboText.setString("Max Combo: " + std::to_string(maxCombo));
    comboText.setPosition(200.f, 290.f);

    // BUTTONS
    backBtn = Button({200, 60}, {50, 450}, font, "Main Menu");
    retryBtn = Button({200, 60}, {450, 450}, font, "Retry");

    // BACKGROUND
    gradient.setSize({700.f, 600.f});
    gradient.setFillColor(sf::Color(40, 20, 90));

    // PARTICLES
    for (int i = 0; i < 12; i++) {
        sf::CircleShape c(5 + rand() % 5);
        c.setFillColor(sf::Color(255, 255, 255, 40));
        c.setPosition(static_cast<float>(rand() % 700), static_cast<float>(rand() % 600));
        particles.push_back(c);
    }
}

void ResultScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
            window.close();

        if (backBtn.isClicked(window, event))
            goTo = WELCOME;

        if (retryBtn.isClicked(window, event))
            goTo = GAMEPLAY;   // your teammate will define GAMEPLAY screen
    }

    backBtn.setHoverColor(backBtn.isHovered(window));
    retryBtn.setHoverColor(retryBtn.isHovered(window));
}

void ResultScreen::update() {
    for (auto& p : particles) {
        sf::Vector2f pos = p.getPosition();
        pos.y -= 0.18f;
        if (pos.y < -10) pos.y = 620;
        p.setPosition(pos);
    }
}

void ResultScreen::draw(sf::RenderWindow& window) {
    window.draw(gradient);

    for (auto& p : particles)
        window.draw(p);

    window.draw(title);
    window.draw(scoreText);
    window.draw(accuracyText);
    window.draw(comboText);

    backBtn.draw(window);
    retryBtn.draw(window);
}

ScreenID ResultScreen::nextScreen() { return goTo; }
void ResultScreen::resetNextScreen() { goTo = NONE; }
