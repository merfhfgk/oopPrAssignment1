//
//  shape.h
//  oopAssignm1
//
//  Created by Maria Goncharuk on 21.09.2026.
//

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include "Board.h"

struct Rect {
    int left, top, right, bottom;
};
class Shape {
protected:
    int id;
    std::string color;
    bool isFilled;
    
public:
    Shape(int id, const std::string& color, bool isFilled) : id(id), color(color), isFilled(isFilled) {}
    virtual ~Shape() = default;
    
    virtual void draw(Board& board) const = 0;
    virtual bool contains(int px, int py) const = 0;
    virtual std::string getInfo() const = 0;
    
    int getId() const { return id; }
    virtual std::string getName() const = 0;
    virtual std::vector<int> getParams() const = 0;
    virtual int getEditParamCount() const = 0;
    virtual void edit(const std::vector<int>& p) = 0;
    virtual void moveTo(int x, int y) = 0;
    virtual bool isValid() const = 0;
    virtual Rect getBounds() const = 0;
    virtual std::unique_ptr<Shape> clone() const = 0;

    std::string getColor() const { return color; }
    bool getIsFilled() const { return isFilled; }
    
    char getColorChar() const{
        return color.empty() ? '*' : color[0];
    }
    
    void setColor(const std::string& newColor) { color = newColor; }

    bool sameAs(const Shape& other) const {
        return typeid(*this) == typeid(other)
            && isFilled == other.isFilled
            && getParams() == other.getParams();
    }
};

#endif // SHAPE_H
