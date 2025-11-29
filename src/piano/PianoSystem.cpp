#include "PianoSystem.hpp"
#include <iostream>
#include <algorithm>

PianoSystem::PianoSystem(float left, float top, float totalWidth)
    : x(left), y(top), width(totalWidth)
{
    // keyboard mapping (B choice)
    keyMap[sf::Keyboard::A] = "C";
    keyMap[sf::Keyboard::W] = "Csharp";
    keyMap[sf::Keyboard::S] = "D";
    keyMap[sf::Keyboard::E] = "Dsharp";
    keyMap[sf::Keyboard::D] = "E";
    keyMap[sf::Keyboard::F] = "F";
    keyMap[sf::Keyboard::T] = "Fsharp";
    keyMap[sf::Keyboard::G] = "G";
    keyMap[sf::Keyboard::Y] = "Gsharp";
    keyMap[sf::Keyboard::H] = "A";
    keyMap[sf::Keyboard::U] = "Asharp";
    keyMap[sf::Keyboard::J] = "B";
    keyMap[sf::Keyboard::K] = "Chigh";

    loadSounds();
    // load font used for labels (ensure the file path is correct at runtime)
    if (!font.loadFromFile("src/resources/fonts/ARIAL.TTF")) {
        std::cerr << "PianoSystem: failed to load font resources/fonts/ARIAL.TTF\n";
        // continue — labels will not render but program won't crash
    }

    buildKeys();
}

void PianoSystem::loadSounds() {
    for (const auto& note : noteNamesAll) {
        std::string path = "src/resources/sounds/" + note + ".wav";
        sf::SoundBuffer buf;
        if (!buf.loadFromFile(path)) {
            std::cerr << "PianoSystem: failed to load sound '" << path << "'\n";
            // continue — missing sound won't crash, but won't play
            continue;
        }
        buffers[note] = std::move(buf);
        sounds[note].setBuffer(buffers[note]);
    }
}

void PianoSystem::buildKeys() {
    whiteKeys.clear();
    blackKeys.clear();

    // Geometry
    const int whiteCount = 7; // C D E F G A B across one octave
    float whiteW = width / static_cast<float>(whiteCount);
    float whiteH = 240.f;

    // base white notes (left to right)
    std::vector<std::string> whiteOrder = {"C","D","E","F","G","A","B"};
    std::vector<std::pair<int,std::string>> blackInfo = {
        {0, "Csharp"},
        {1, "Dsharp"},
        // skip between E-F
        {3, "Fsharp"},
        {4, "Gsharp"},
        {5, "Asharp"}
    };

    // create white keys
    for (int i = 0; i < whiteCount; ++i) {
        PianoKey k;
        k.name = whiteOrder[i];
        k.isBlack = false;
        k.rect.setSize({whiteW, whiteH});
        k.rect.setPosition(x + i * whiteW, y);
        k.rect.setOutlineThickness(2.f);
        k.rect.setOutlineColor(sf::Color::Black);
        k.rect.setFillColor(k.whiteColor);
        whiteKeys.push_back(std::move(k));
    }

    // create black keys (narrower, shorter, positioned between whites)
    float blackW = whiteW * 0.6f;
    float blackH = whiteH * 0.62f;

    for (auto &p : blackInfo) {
        int leftWhiteIndex = p.first; // index of left white key
        const std::string& name = p.second;

        float center = x + leftWhiteIndex * whiteW + whiteW; // center between white[left] and white[left+1]
        float bx = center - blackW / 2.f;

        PianoKey bk;
        bk.name = name;
        bk.isBlack = true;
        bk.rect.setSize({blackW, blackH});
        bk.rect.setPosition(bx, y);
        bk.rect.setOutlineThickness(2.f);
        bk.rect.setOutlineColor(sf::Color::Black);
        bk.rect.setFillColor(bk.blackColor);
        blackKeys.push_back(std::move(bk));
    }

    // Add high C (right of the last white)
    PianoKey highC;
    highC.name = "Chigh";
    highC.isBlack = false;
    highC.rect.setSize({whiteW, whiteH});
    highC.rect.setPosition(x + whiteCount * whiteW, y); // immediately right
    highC.rect.setOutlineThickness(2.f);
    highC.rect.setOutlineColor(sf::Color::Black);
    highC.rect.setFillColor(highC.whiteColor);
    whiteKeys.push_back(std::move(highC)); // now whiteKeys.size() == 8 (C..B + C_high)
}

void PianoSystem::playNote(const std::string& note) {
    auto it = sounds.find(note);
    if (it != sounds.end()) {
        it->second.play();
    } else {
        // silent if missing
        // std::cerr << "No sound buffer for note: " << note << "\n";
    }
}

const std::string* PianoSystem::hitTestBlack(float px, float py) {
    for (const auto& k : blackKeys) {
        if (k.rect.getGlobalBounds().contains(px, py))
            return &k.name;
    }
    return nullptr;
}

const std::string* PianoSystem::hitTestWhite(float px, float py) {
    for (const auto& k : whiteKeys) {
        if (k.rect.getGlobalBounds().contains(px, py))
            return &k.name;
    }
    return nullptr;
}

void PianoSystem::handleEvent(sf::RenderWindow& window, const sf::Event& event) {
    // Mouse press: check black first
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f worldPos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

        if (const std::string* b = hitTestBlack(worldPos.x, worldPos.y)) {
            // mark pressed visually
            for (auto& bk : blackKeys) {
                if (bk.name == *b) { bk.pressed = true; bk.rect.setFillColor(bk.blackPressed); break; }
            }
            playNote(*b);
            return;
        }

        if (const std::string* w = hitTestWhite(worldPos.x, worldPos.y)) {
            for (auto& wk : whiteKeys) {
                if (wk.name == *w) { wk.pressed = true; wk.rect.setFillColor(wk.whitePressed); break; }
            }
            playNote(*w);
            return;
        }
    }
    

    // Keyboard press
    if (event.type == sf::Event::KeyPressed) {
        auto it = keyMap.find(event.key.code);
        if (it != keyMap.end()) {
            const std::string& note = it->second;
            // visual: find key and mark pressed
            bool found = false;
            for (auto& bk : blackKeys) {
                if (bk.name == note) { bk.pressed = true; bk.rect.setFillColor(bk.blackPressed); found = true; break; }
            }
            if (!found) {
                for (auto& wk : whiteKeys) {
                    if (wk.name == note) { wk.pressed = true; wk.rect.setFillColor(wk.whitePressed); break; }
                }
            }
            playNote(note);
        }
    }

    // Mouse move -> hover effects (optional)
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f worldPos = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        for (auto& bk : blackKeys) {
            if (bk.rect.getGlobalBounds().contains(worldPos))
                bk.rect.setFillColor(bk.blackHover);
            else if (!bk.pressed)
                bk.rect.setFillColor(bk.blackColor);
        }
        for (auto& wk : whiteKeys) {
            if (wk.rect.getGlobalBounds().contains(worldPos))
                wk.rect.setFillColor(wk.whiteHover);
            else if (!wk.pressed)
                wk.rect.setFillColor(wk.whiteColor);
        }
    }

    // Mouse release can clear pressed state (we also clear in update)
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        // optionally keep visual for a short time; immediate clear:
        for (auto& bk : blackKeys) if (bk.pressed) { bk.pressed = false; bk.rect.setFillColor(bk.blackColor); }
        for (auto& wk : whiteKeys) if (wk.pressed) { wk.pressed = false; wk.rect.setFillColor(wk.whiteColor); }
    }
}
std::string PianoSystem::getPressedNote(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        auto it = keyMap.find(event.key.code);
        if (it != keyMap.end()) {
            return it->second;   // return mapped note name
        }
    }
    return "";
}

void PianoSystem::update(float dt) {
    // simple reset of pressed flags so press flashes for one frame
    // if you want sustain, remove this or add timers
    for (auto& bk : blackKeys) {
        if (bk.pressed) {
            // keep pressed for a tiny bit then reset
            bk.pressed = false;
            bk.rect.setFillColor(bk.blackColor);
        }
    }
    for (auto& wk : whiteKeys) {
        if (wk.pressed) {
            wk.pressed = false;
            wk.rect.setFillColor(wk.whiteColor);
        }
    }
}

void PianoSystem::draw(sf::RenderWindow& target) const {
    // draw white keys in order
    for (const auto& wk : whiteKeys) target.draw(wk.rect);
    // draw black keys on top
    for (const auto& bk : blackKeys) target.draw(bk.rect);
    // draw labels
    sf::Text label;
    label.setFont(font);

    // white key labels
    label.setFillColor(sf::Color::Black);
    label.setCharacterSize(20);

    for (const auto& wk : whiteKeys) {
        label.setString(wk.name);
        float lx = wk.rect.getPosition().x + wk.rect.getSize().x * 0.35f;
        float ly = wk.rect.getPosition().y + wk.rect.getSize().y * 0.75f;
        label.setPosition(lx, ly);
        target.draw(label);
    }

    // black key labels
    label.setFillColor(sf::Color::White);
    label.setCharacterSize(15);

    for (const auto& bk : blackKeys) {
        label.setString(bk.name);
        float lx = bk.rect.getPosition().x + bk.rect.getSize().x * 0.15f;
        float ly = bk.rect.getPosition().y + bk.rect.getSize().y * 0.2f;
        label.setPosition(lx, ly);
        target.draw(label);
    }
}

void PianoSystem::resetAllKeyColors() {
    for (auto& wk : whiteKeys) wk.rect.setFillColor(wk.whiteColor);
    for (auto& bk : blackKeys) bk.rect.setFillColor(bk.blackColor);
}
