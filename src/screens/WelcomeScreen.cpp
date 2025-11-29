#include "WelcomeScreen.hpp"
#include <cmath>

WelcomeScreen::WelcomeScreen() {
    // Load font (src/resources/fonts/arial.ttf)
    font.loadFromFile("src/resources/fonts/ARIAL.TTF");

    // Title
    title.setFont(font);
    title.setString("PIANO MEMORY");
    title.setCharacterSize(52);
    title.setFillColor(sf::Color::White);
    sf::FloatRect t = title.getLocalBounds();
    title.setOrigin(t.width / 2, t.height / 2);
    title.setPosition(350.f, 80.f);

    // Gradient background
    gradient.setSize({700.f, 600.f});
    gradient.setFillColor(sf::Color(40, 20, 90));

    // Particles
    for (int i = 0; i < 12; i++) {
        sf::CircleShape c(5 + rand() % 5);
        c.setFillColor(sf::Color(255, 255, 255, 40));
        c.setPosition(static_cast<float>(rand() % 700), static_cast<float>(rand() % 600));
        particles.push_back(c);
    }

    // Buttons
    startBtn = Button({300, 70}, {200, 200}, font, "Start Game");
    freeBtn  = Button({300, 70}, {200, 300}, font, "Free Play");
    exitBtn  = Button({300, 70}, {200, 400}, font, "Exit");

    // Background music (optional)
    if (bgMusic.openFromFile("src/resources/sounds/soft-piano.wav")) {
        bgMusic.setLoop(true);
        bgMusic.setVolume(30);
        bgMusic.play();
    }
}

void WelcomeScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (freeBtn.isClicked(window, event)) {
            next = FREEPLAY;
        }
        if (startBtn.isClicked(window, event)) {
            next = GAMEMODE;
        }
        if (exitBtn.isClicked(window, event)) {
            window.close();
        }
    }

    // Hover effects
    startBtn.setHoverColor(startBtn.isHovered(window));
    freeBtn.setHoverColor(freeBtn.isHovered(window));
    exitBtn.setHoverColor(exitBtn.isHovered(window));
}

void WelcomeScreen::update() {
    glowTimer += 0.03f;
    float glow = 180.f + std::sin(glowTimer) * 75.f;
    float g = std::min(255.0f, glow);
    title.setFillColor(sf::Color(static_cast<sf::Uint8>(g), static_cast<sf::Uint8>(g), 255));

    for (auto& p : particles) {
        sf::Vector2f pos = p.getPosition();
        pos.y -= 0.2f;
        if (pos.y < -10) pos.y = 620;
        p.setPosition(pos);
    }
}

void WelcomeScreen::draw(sf::RenderWindow& window) {
    window.draw(gradient);
    for (auto& p : particles) window.draw(p);
    window.draw(title);
    startBtn.draw(window);
    freeBtn.draw(window);
    exitBtn.draw(window);
}

ScreenID WelcomeScreen::nextScreen() { return next; }
void WelcomeScreen::resetNextScreen() { next = NONE; }
//g++ src/*.cpp src/screens/*.cpp -Iinclude -o PianoGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
