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

#endif // SHAPE_H
