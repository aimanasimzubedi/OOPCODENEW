#ifndef PIANO_SYSTEM_HPP
#define PIANO_SYSTEM_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

struct PianoKey {
    std::string name;
    sf::RectangleShape rect;
    bool isBlack = false;
    bool pressed = false;

    // default colors
    sf::Color whiteColor   = sf::Color(250,250,255);
    sf::Color whiteHover   = sf::Color(220,220,255);
    sf::Color whitePressed = sf::Color(190,190,240);

    sf::Color blackColor   = sf::Color(30,30,30);
    sf::Color blackHover   = sf::Color(50,50,60);
    sf::Color blackPressed = sf::Color(90,90,110);
};

class PianoSystem {
public:
    PianoSystem(float left = 0.f, float top = 330.f, float totalWidth = 700.f);

    // loads sounds and builds keys (called in ctor)
    void loadSounds();
    void buildKeys();

    // event driven: call from your screen's event loop
    void handleEvent(sf::RenderWindow& window, const sf::Event& event);

    // update visuals / reset pressed flags if needed
    void update(float dt = 0.f);

    // draw keys (white then black)
    void draw(sf::RenderWindow& target) const;

    // reset all key visuals to default (call when leaving a screen)
    void resetAllKeyColors();

private:
    // geometry / layout
    float x;      // left origin
    float y;      // top origin of keys
    float width;  // total piano width

    // keys (preserve order for drawing)
    std::vector<PianoKey> whiteKeys;
    std::vector<PianoKey> blackKeys;

    // audio
    std::map<std::string, sf::SoundBuffer> buffers;
    std::map<std::string, sf::Sound> sounds;

    // keyboard -> note mapping
    std::unordered_map<sf::Keyboard::Key, std::string> keyMap;

    // master note list used for loading
    const std::vector<std::string> noteNamesAll = {
        "C", "Csharp", "D", "Dsharp", "E", "F",
        "Fsharp", "G", "Gsharp", "A", "Asharp", "B", "Chigh"
    };

    // helpers
    void playNote(const std::string& note);
    const std::string* hitTestBlack(float px, float py);
    const std::string* hitTestWhite(float px, float py);
};

#endif // PIANO_SYSTEM_HPP
