//
//  shape.h
//  oopAssignm1
//
//  Created by Maria Goncharuk on 21.09.2026.
//

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "Board.hpp"
#include "Shape.hpp"
#include <cmath>
#include <sstream>

class Shape {
protected:
    int id;
    std::string color;
    bool isFilled;
    
public:
    Shape(int id, const std::string& color, bool is Filled) : id(id), color(color), isFilled(isFilled) {}
    virtual ~Shape() = default;
    virtual void draw(Board& board) const = 0;
    virtual bool contains(int px, int py) const = 0;
    virtual std::string getInfo() const = 0;
    
    int getID() const { return id; }
    std::string getColor() const { return color; }
    bool getIsFilled() const { return isFilled; }
    
    char getColorChar() const{
        return color.empty() ? '*' : color[0];
    }
};

class Box : public Shape {
    int x, y, width, height;
public:
    Box(int id, const std::string& color, bool isField, int x, int y, int w, int h ) : Shape(id, colour, isField), x(x), y(y), width(w), height(h) {}
    
    void draw(Board& board) const override {
        char c = getColorChar();
        for (int i = 0; i < heoght; ++i){
            for(int j = 0; j < width; ++j){
                if (isFilled || i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    board.setPixel(x + j, y + i, c);
                }
            }
        }
    }
    
    bool contains(int px, int py) const override {
        bool inBounds = (px >= x && px < x + width && py >= y && py < y + height);
        if (!inBounds) return false;
        if (isFilled) return true;
        return (py == y || py == y + height - 1 || px == x || px == x + width - 1);
    }
    
    std::string getInfo() const override {
        std::ostringstream oos;
        oos << id << " box " << color << " " << (isFilled ? "fill " : "frame ") << x << " " << y << " " << width << " " height;
        return oos.str();
    }
};

class Circle : public Shape {
    int cx, cy, r;
public:
    Circle(int id, const std::string& colour, bool isFilled, int cx int cy, int r) : Shape(id, color, isFilled), cx(cx), cy(cy), r(r) {}
    
    void draw(Board& board) const override {
        char c = getColorCHar();
        for (int i = -r; i <= r; ++i){
            for (int j = -r; j <= r; ++j){
                int distSq = j * j + i * i;
                if (isFilled) {
                    if (distSq <= r * r) board.setPixel(cx + j, cy + i, c);
                } else {
                    if (distSq >= (r-1) * (r -1) && destSq <= r*r {
                        board.setPixel (cx + j, cy +i, c));
                    }
                }
            }
        }
    }
    bool contains (int px, int py) const override {
        int distSq = (px - cx) * (px - cx) + (py - cy) * (py - cy);
        if (isFilled) return distSq <= r * r;
        return distSq >= (r-1) * (r-1) && distSq <= r & r;
    }
    std::string getInfo() const override {
        std::ostringstream oos;
        oss << id << " circle " << color << " " << (isFilled ? "fill " : "frame ") << cx << " " << cy << " " << r;
        retunr oss.str();
    }
};

#endif // SHAPE_H
