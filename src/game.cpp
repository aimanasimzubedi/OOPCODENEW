#include "game.hpp"
#include "screens\WelcomeScreen.hpp"
#include "screens\FreePlayScreen.hpp"
#include "screens\MainScreen.hpp"
#include "screens\GameModeScreen.hpp"
#include "screens\ResultScreen.hpp"

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
        case GAMEMODE: return new GameModeScreen();
        case RESULT: return new ResultScreen(score, accuracy, maxCombo, finalTime);
        default: return nullptr;
    }
}

void Game::processScreenSwitch() {
    if (!current) return;
    ScreenID next = current->nextScreen();
    if (next != NONE) {
        // If leaving GameMode, extract the stats
        if (auto gm = dynamic_cast<GameModeScreen*>(current)) {
            score = gm->getScore();
            accuracy = gm->getAccuracy();
            maxCombo = gm->getMaxCombo();
            finalTime = gm->getTime();
        }


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
