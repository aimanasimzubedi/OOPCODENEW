#include "Object.hpp"

// default constructor
Object::Object()
    : x(0), y(0), width(0), height(0) {}

// parameterized constructor
Object::Object(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {}

void Object::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

void Object::setSize(float newWidth, float newHeight) {
    width = newWidth;
    height = newHeight;
}

float Object::getX() const { return x; }
float Object::getY() const { return y; }
float Object::getWidth() const { return width; }
float Object::getHeight() const { return height; }
