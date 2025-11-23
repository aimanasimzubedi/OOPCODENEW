#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SFML/Graphics.hpp>

class Object {
protected:
    float x, y;          // base position
    float width, height; // base size

public:
    Object();
    Object(float x, float y, float width, float height);

    virtual ~Object() {}

    // setters
    void setPosition(float newX, float newY);
    void setSize(float newWidth, float newHeight);

    // getters
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

    // virtual if needed for drawing
    virtual void draw(sf::RenderWindow& window) = 0;
};

#endif
