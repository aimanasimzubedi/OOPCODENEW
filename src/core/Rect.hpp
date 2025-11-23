#ifndef RECT_HPP
#define RECT_HPP

#include "Object.hpp"
#include <SFML/Graphics.hpp>

class Rect : public Object {
public:
    Rect() = default;
    virtual ~Rect() = default;

    virtual void setPosition(const sf::Vector2f& pos) { shape.setPosition(pos); }
    virtual void setSize(const sf::Vector2f& s) { shape.setSize(s); }
    virtual const sf::FloatRect getGlobalBounds() const { return shape.getGlobalBounds(); }
    virtual void render(sf::RenderTarget& target) { target.draw(shape); }

protected:
    sf::RectangleShape shape;
};

#endif // RECT_HPP
