//
//  Box.h
//  oopAssignm1
//
//  Created by Maria Goncharuk on 29.09.2026.
//

#include "Shape.h"
#include <cmath>
#include <sstream>

class Box : public Shape {
    int x, y, width, height;
public:
    Box(int id, const std::string& color, bool isField, int x, int y, int w, int h ) : Shape(id, colour, isField), x(x), y(y), width(w), height(h) {}
    void draw(Board& board) const override {
        char c = getColorChar();
        for (int i = 0; i < heoght; i++){
            for(int j = 0; j < width; j++){
                if (isField || i == 0 || i == height - 1 || j == 0 || j == width - 1) {
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
}

#endif // BOX_H
