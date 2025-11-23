#include "Button.hpp"

Button::Button() {}

Button::Button(sf::Vector2f size, sf::Vector2f position, const sf::Font& font, const std::string& label) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(70, 70, 70));          // button shape, color, position

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);                // button text properties

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2, bounds.height / 2);
    text.setPosition(position.x + size.x / 2, position.y + size.y / 2 - 5);     // Center text
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isHovered(sf::RenderWindow& window) {
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    return shape.getGlobalBounds().contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y));
}

bool Button::isClicked(sf::RenderWindow& window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        return isHovered(window);
    }
    return false;
}

void Button::setHoverColor(bool hover) {
    if (hover) {
        shape.setFillColor(sf::Color(90, 90, 90));
    } else {
        shape.setFillColor(sf::Color(70, 70, 70));
    }
}
