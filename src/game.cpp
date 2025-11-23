#include "game.hpp"
#include "screens\WelcomeScreen.hpp"
#include "screens\FreePlayScreen.hpp"
#include "screens\MainScreen.hpp"

Game::Game(unsigned int w, unsigned int h, const std::string& title)
: window(sf::VideoMode(w, h), title)
{
    window.setFramerateLimit(60);
    current = createScreen(WELCOME);
}

Game::~Game() {
    if (current) delete current;
}

Screen* Game::createScreen(ScreenID id) {
    switch (id) {
        case WELCOME: return new WelcomeScreen();
        case FREEPLAY: return new FreePlayScreen();
        case MAINGAME: return new MainGameScreen();
        default: return nullptr;
    }
}

void Game::processScreenSwitch() {
    if (!current) return;
    ScreenID next = current->nextScreen();
    if (next != NONE) {
        Screen* old = current;
        current = createScreen(next);
        old->resetNextScreen();
        delete old;
    }
}

void Game::run() {
    while (window.isOpen()) {
        if (current) current->handleEvents(window);
        if (current) current->update();

        processScreenSwitch();

        window.clear();
        if (current) current->draw(window);
        window.display();
    }
}
