#include "MainScreen.hpp"
#include "..\piano\PianoSystem.hpp"


MainGameScreen::MainGameScreen()
    : piano(0.f, 330.f, 700.f)
{
    font.loadFromFile("src/resources/fonts/ARIAL.TTF");
    title.setFont(font);
    title.setString("Main Game Mode");
    title.setCharacterSize(42);
    title.setFillColor(sf::Color::White);
    sf::FloatRect tb = title.getLocalBounds();
    title.setOrigin(tb.width / 2, tb.height / 2);
    title.setPosition(350.f, 60.f);

    backBtn = Button({100, 50}, {20, 20}, font, "Quit");

    gradient.setSize({700.f, 600.f});
    gradient.setFillColor(sf::Color(40, 20, 90));

    for (int i = 0; i < 10; i++) {
        sf::CircleShape c(5 + rand() % 4);
        c.setFillColor(sf::Color(255, 255, 255, 40));
        c.setPosition(static_cast<float>(rand() % 700), static_cast<float>(rand() % 600));
        particles.push_back(c);
    }
}

void MainGameScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        piano.handleEvent(window, event);

        if (backBtn.isClicked(window, event)) {
            goTo = WELCOME;
        }
    }

    backBtn.setHoverColor(backBtn.isHovered(window));
}

void MainGameScreen::update() {
    piano.update();

    for (auto& p : particles) {
        sf::Vector2f pos = p.getPosition();
        pos.y -= 0.18f;
        if (pos.y < -10) pos.y = 620;
        p.setPosition(pos);
    }
}

void MainGameScreen::draw(sf::RenderWindow& window) {
    window.draw(gradient);
    for (const auto& particle : particles) window.draw(particle);

    // draw piano
    piano.draw(window);

    window.draw(title);
    backBtn.draw(window);
}

ScreenID MainGameScreen::nextScreen() { return goTo; }
void MainGameScreen::resetNextScreen() { goTo = NONE; }
