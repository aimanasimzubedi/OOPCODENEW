#include "GameModeScreen.hpp"
#include <ctime>
#include <cstdlib>

GameModeScreen::GameModeScreen()
    : goBtn({180, 60}, {260, 450}, font, "GO"),
      doneBtn({180, 60}, {260, 520}, font, "Done"),
      exitBtn({150, 50}, {20, 20}, font, "Exit")
{
    font.loadFromFile("src/resources/fonts/ARIAL.TTF");

    sequenceText.setFont(font);
    sequenceText.setCharacterSize(32);
    sequenceText.setFillColor(sf::Color::White);
    sequenceText.setPosition(50, 150);

    timerText.setFont(font);
    timerText.setCharacterSize(28);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(500, 20);

    // generate 5-note sequence
    noteSequence = generateSequence(5);

    std::string seq = "Play: ";
    for (auto &s : noteSequence) seq += s + "    ";
    sequenceText.setString(seq);
}

std::vector<std::string> GameModeScreen::generateSequence(int length){
    std::vector<std::string> notes = {
        "C", "C#",
        "D", "D#",
        "E",
        "F", "F#",
        "G", "G#",
        "A", "A#",
        "B"
    };
    std::vector<std::string> seq;

    srand(time(NULL));
    for(int i=0;i<length;i++){
        seq.push_back(notes[rand()%notes.size()]);
    }
    return seq;
}

void GameModeScreen::handleEvents(sf::RenderWindow& window){
    sf::Event event;

    while (window.pollEvent(event)){
        
        if (event.type == sf::Event::Closed)
            window.close();

        // 1. EXIT
        if (exitBtn.isClicked(window, event))
            goTo = WELCOME;

        // 2. GO → start game
        if (!gameStarted && goBtn.isClicked(window, event)){
            gameStarted = true;

            elapsedTime = 0.f;
            correctPresses = 0;
            totalPresses = 0;
            score = 0;
            combo = 0;
            maxCombo = 0;
            return;
        }

        // 3. DONE → stop BEFORE any piano input
        if (gameStarted && doneBtn.isClicked(window, event)){
            gameStarted = false;

            if (totalPresses == 0) accuracy = 0;
            else accuracy = (correctPresses * 100.0f) / totalPresses;

            goTo = RESULT;
            return;
        }

        // 4. PIANO INPUT ONLY AFTER GAME STARTS
        if (gameStarted){

            // KEYBOARD input
            piano.handleEvent(window, event);
            std::string pressed = piano.getPressedNote(event);

            // KEYBOARD scoring
            if (!pressed.empty()){
                totalPresses++;

                if (correctPresses < noteSequence.size() &&
                    pressed == noteSequence[correctPresses])
                {
                    correctPresses++;
                    combo++;
                    maxCombo = std::max(maxCombo, combo);
                }
                else combo = 0;

                score = (correctPresses * 100.0f) / noteSequence.size();
            }

            // MOUSE input + scoring (fixed version)
            if (event.type == sf::Event::MouseButtonPressed){
                sf::Vector2f worldPos = window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });

                auto name = piano.hitTestBlack(worldPos.x, worldPos.y);
                if (!name) name = piano.hitTestWhite(worldPos.x, worldPos.y);

                if (name){
                    std::string mpressed = *name;

                    totalPresses++;

                    if (correctPresses < noteSequence.size() &&
                        mpressed == noteSequence[correctPresses])
                    {
                        correctPresses++;
                        combo++;
                        maxCombo = std::max(maxCombo, combo);
                    }
                    else combo = 0;

                    score = (correctPresses * 100.0f) / noteSequence.size();
                }
            }
        }
    }
}

void GameModeScreen::update(){
    if(gameStarted){
        elapsedTime += 0.016f;
    }
}

void GameModeScreen::draw(sf::RenderWindow& window){
    window.clear(sf::Color(20,20,50));

    exitBtn.draw(window);

    if(!gameStarted){
        window.draw(sequenceText);
        goBtn.draw(window);
    } 
    else {
        piano.update();
        piano.draw(window);

        window.draw(sequenceText);

        timerText.setString("Time: " + std::to_string((int)elapsedTime));
        window.draw(timerText);

        doneBtn.draw(window);
    }
}

ScreenID GameModeScreen::nextScreen(){ return goTo; }
void GameModeScreen::resetNextScreen(){ goTo = NONE; }
