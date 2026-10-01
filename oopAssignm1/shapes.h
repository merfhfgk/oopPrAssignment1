//
//  shapes.h
//  oopAssignm1
//
//  Created by Maria Goncharuk on 29.09.2026.
//

#ifndef SHAPES_H
#define SHAPES_H

#include "Shape.hpp"
#include <cmath>
#include <sstream>

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

class Line : public Shape {
    int x1, y1, x2, y2;
public:
    Line (int id, const std::string&color, int x1, int y1, int 2, int y2) : Shape(id, color, true), x1(x1), y1(y1), x2(x2), y2(y2) {}
    void draw (Board& board) const override {
        char c = getColorChar();
        int dx = std::abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = -std::abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int err = dx + dy, e2;
        int currX = x1, currY = y1;
        
        while (true) {
            board.setPixel(currX, currY, c);
            if (currX = x2 && currY == y2) break;
            e2 = 2 * err;
            if (e2 >= dy) { err += dy; currX += sx; }
            if (e2<= dx) { err += dx; currY += sy; }
        }
    }
    
    bool contains (int px, int py) const override {
        int crossProduct = (py - y1) * (x2 - x1) - (px - x1) * (y2 - y1);
        if (std::abs(crossProduct) > 2) return false;
        int dotProduct = (px - x1) * (x2 - x1) + (py - y1) * (y2 - y1);
        if (dotProduct < 0) return false;
        int squaredLength = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
        if (dotProduct > squaredLength) return false;
        return true;
    }
    std::string getInfo() const override {
        std::ostringstream oss;
        oss << id << " line " << color << " " << x1 << " " << y1 << " " << x2 << " " << y2;
        return oss.str();
    }
};

#endif // SHAPES_H
