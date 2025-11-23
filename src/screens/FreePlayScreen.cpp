#include "FreePlayScreen.hpp"
#include "..\piano\PianoSystem.hpp"


FreePlayScreen::FreePlayScreen()
    : piano(0.f, 330.f, 700.f) // position x=0, y=330, width=700 (matches your layout)
{
    // FONT + TITLE
    font.loadFromFile("src/resources/fonts/ARIAL.TTF");
    title.setFont(font);
    title.setString("Free Play Mode");
    title.setCharacterSize(42);
    title.setFillColor(sf::Color::White);
    sf::FloatRect tb = title.getLocalBounds();
    title.setOrigin(tb.width / 2, tb.height / 2);
    title.setPosition(350.f, 60.f);

    // BACK BUTTON (top-left)
    backBtn = Button({150, 50}, {20, 20}, font, "Menu");

    // BACKGROUND
    gradient.setSize({700.f, 600.f});
    gradient.setFillColor(sf::Color(40, 20, 90));

    // Particles
    for (int i = 0; i < 10; i++) {
        sf::CircleShape c(5 + rand() % 4);
        c.setFillColor(sf::Color(255, 255, 255, 40));
        c.setPosition(static_cast<float>(rand() % 700), static_cast<float>(rand() % 600));
        particles.push_back(c);
    }
}

void FreePlayScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        // Give piano first chance to handle input (mouse, keys)
        piano.handleEvent(window, event);

        if (backBtn.isClicked(window, event)) goTo = WELCOME;
    }

    // Hover detection for UI button
    backBtn.setHoverColor(backBtn.isHovered(window));
}

void FreePlayScreen::update() {
    piano.update();

    for (auto& p : particles) {
        sf::Vector2f pos = p.getPosition();
        pos.y -= 0.18f;
        if (pos.y < -10) pos.y = 620;
        p.setPosition(pos);
    }
}

void FreePlayScreen::draw(sf::RenderWindow& window) {
    window.draw(gradient);
    for (auto& p : particles) window.draw(p);
    window.draw(title);
    backBtn.draw(window);

    // draw piano (white then black keys internally)
    piano.draw(window);
}

ScreenID FreePlayScreen::nextScreen() { return goTo; }
void FreePlayScreen::resetNextScreen() { goTo = NONE; }
