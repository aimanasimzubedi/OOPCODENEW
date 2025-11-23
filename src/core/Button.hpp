#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;

public:
    Button();
    Button(sf::Vector2f size, sf::Vector2f position, const sf::Font& font, const std::string& label);

    void draw(sf::RenderWindow& window);
    bool isHovered(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window, sf::Event event);
    void setHoverColor(bool hover);
};

#endif // BUTTON_HPP
