//
//  shapes.h
//  oopAssignm1
//
//  Created by Maria Goncharuk on 29.09.2026.
//

#ifndef SHAPES_H
#define SHAPES_H

#include "Shape.h"
#include <cmath>
#include <algorithm>
#include <sstream>

class Box : public Shape {
    int x, y, width, height;
public:
    Box(int id, const std::string& color, bool isFilled, int x, int y, int w, int h) : Shape(id, color, isFilled), x(x), y(y), width(w), height(h) {}

    void draw(Board& board) const override {
        char c = getColorChar();
        for (int i = 0; i < height; ++i){
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
        std::ostringstream oss;
        oss << id << " box " << (isFilled ? "fill " : "frame ") << color << " "
            << x << " " << y << " " << width << " " << height;
        return oss.str();
    }

    std::string getName() const override { return "box"; }
    std::vector<int> getParams() const override { return {x, y, width, height}; }
    int getEditParamCount() const override { return 2; }   // width height
    void edit(const std::vector<int>& p) override { width = p[0]; height = p[1]; }
    void moveTo(int newX, int newY) override { x = newX; y = newY; }
    bool isValid() const override { return width > 0 && height > 0; }
    Rect getBounds() const override { return {x, y, x + width - 1, y + height - 1}; }
    std::unique_ptr<Shape> clone() const override { return std::make_unique<Box>(*this); }
};

class Circle : public Shape {
    int cx, cy, r;
public:
    Circle(int id, const std::string& color, bool isFilled, int cx, int cy, int r)
        : Shape(id, color, isFilled), cx(cx), cy(cy), r(r) {}

    void draw(Board& board) const override {
        char c = getColorChar();
        for (int i = -r; i <= r; ++i){
            for (int j = -r; j <= r; ++j){
                int distSq = j * j + i * i;
                if (isFilled) {
                    if (distSq <= r * r) board.setPixel(cx + j, cy + i, c);
                } else {
                    if (distSq >= (r-1) * (r -1) && distSq <= r*r) {
                        board.setPixel (cx + j, cy +i, c);
                    }
                }
            }
        }
    }
    
    bool contains (int px, int py) const override {
        int distSq = (px - cx) * (px - cx) + (py - cy) * (py - cy);
        if (isFilled) return distSq <= r * r;
        return distSq >= (r-1) * (r-1) && distSq <= r * r;
    }
    
    std::string getInfo() const override {
        std::ostringstream oss;
        oss << id << " circle " << (isFilled ? "fill " : "frame ") << color << " "
            << cx << " " << cy << " " << r;
        return oss.str();
    }

    std::string getName() const override { return "circle"; }
    std::vector<int> getParams() const override { return {cx, cy, r}; }
    int getEditParamCount() const override { return 1; }   // radius
    void edit(const std::vector<int>& p) override { r = p[0]; }
    void moveTo(int newX, int newY) override { cx = newX; cy = newY; }
    bool isValid() const override { return r > 0; }
    Rect getBounds() const override { return {cx - r, cy - r, cx + r, cy + r}; }
    std::unique_ptr<Shape> clone() const override { return std::make_unique<Circle>(*this); }
};

class Line : public Shape {
    int x1, y1, x2, y2;
public:
    Line(int id, const std::string& color, bool isFilled, int x1, int y1, int x2, int y2)
        : Shape(id, color, isFilled), x1(x1), y1(y1), x2(x2), y2(y2) {}

    void draw(Board& board) const override {
        char c = getColorChar();
        int dx = std::abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = -std::abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int err = dx + dy, e2;
        int currX = x1, currY = y1;
        
        while (true) {
            board.setPixel(currX, currY, c);
            if (currX == x2 && currY == y2) break;
            e2 = 2 * err;
            if (e2 >= dy) { err += dy; currX += sx; }
            if (e2<= dx) { err += dx; currY += sy; }
        }
    }

    bool contains (int px, int py) const override {
        int dx = std::abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = -std::abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int err = dx + dy, e2;
        int currX = x1, currY = y1;

        while (true) {
            if (currX == px && currY == py) return true;
            if (currX == x2 && currY == y2) break;
            e2 = 2 * err;
            if (e2 >= dy) { err += dy; currX += sx; }
            if (e2 <= dx) { err += dx; currY += sy; }
        }
        return false;
    }
    std::string getInfo() const override {
        std::ostringstream oss;
        oss << id << " line " << (isFilled ? "fill " : "frame ") << color << " "
            << x1 << " " << y1 << " " << x2 << " " << y2;
        return oss.str();
    }

    std::string getName() const override { return "line"; }
    std::vector<int> getParams() const override { return {x1, y1, x2, y2}; }
    int getEditParamCount() const override { return 2; }   // новий кінець: x2 y2
    void edit(const std::vector<int>& p) override { x2 = p[0]; y2 = p[1]; }
    void moveTo(int newX, int newY) override {
        x2 += newX - x1;
        y2 += newY - y1;
        x1 = newX;
        y1 = newY;
    }
    bool isValid() const override { return true; }
    Rect getBounds() const override {
        return {std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2)};
    }
    std::unique_ptr<Shape> clone() const override { return std::make_unique<Line>(*this); }
};

class Triangle : public Shape {
    int tx, ty, height;
public:
    Triangle(int id, const std::string& color, bool isFilled, int tx, int ty, int height) : Shape(id, color, isFilled), tx(tx), ty(ty), height(height) {}
    
    void draw(Board& board) const override {
        char c = getColorChar();
        for (int i = 0; i < height; ++i) {
            int numStars = 2 * i + 1;
            int leftMost = tx - i;
            for (int j = 0; j < numStars; ++j) {
                if (isFilled || j == 0 || j == numStars - 1 || i == height - 1) {
                    board.setPixel(leftMost + j, ty + i, c);
                }
            }
        }
    }
    
    bool contains(int px, int py) const override {
        if (py < ty || py >= ty + height) return false;
        int i = py - ty;
        int leftMost = tx - i;
        int rightMost = tx + i;
        if (px < leftMost || px > rightMost) return false;
        if (isFilled) return true;
        return px == leftMost || px == rightMost || py == ty + height - 1;
    }
    
    std::string getInfo() const override {
        std::ostringstream oss;
        oss << id << " triangle " << (isFilled ? "fill " : "frame ") << color << " "
            << tx << " " << ty << " " << height;
        return oss.str();
    }

    std::string getName() const override { return "triangle"; }
    std::vector<int> getParams() const override { return {tx, ty, height}; }
    int getEditParamCount() const override { return 1; }   // height
    void edit(const std::vector<int>& p) override { height = p[0]; }
    void moveTo(int newX, int newY) override { tx = newX; ty = newY; }
    bool isValid() const override { return height > 0; }
    Rect getBounds() const override { return {tx - (height - 1), ty, tx + (height - 1), ty + height - 1}; }
    std::unique_ptr<Shape> clone() const override { return std::make_unique<Triangle>(*this); }
};

#endif // SHAPES_H
