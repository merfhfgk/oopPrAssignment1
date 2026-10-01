//
//  shapeManager.h
//  oopAssignm1
//
//  Created by Maria Goncharuk on 30.10.2026.
//

#ifndef SHAPE_MANAGER_H
#define SHAPE_MANAGER_H

#include "Board.hpp"
#include "Shape.hpp"
#include "Shapes.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>


class ShapeManager {
private:
    Board board;
    std::vector<std::unique_ptr<Shape>> shapes;
    int nextId = 1;
    int selectedId = -1;
    
    Shape* findShapeById(int id) {
        for (auto& s : shapes) {
            if (s->getId() == id) return s.get();
        }
        return nullptr;
    }
public:
    void drawBoard() {
        board.clear();
        for (auto& s : shapes) {
            s->draw(board);
        }
        board.print();
    }
    
    void addShape(const std::string& type, const std::string& color, bool isFilled, const std::vector<int>& params) {
        std::unique_ptr<Shape> newShape = nullptr;
        if (type == "box" && params.size() >= 4) {
            newShape = std::make_unique<Box>(nextId++, color, isFilled, params[0], params[1], params[2], params[3]);
        } else if (type == "circle" && params.size() >= 3) {
            newShape = std::make_unique<Circle>(nextId++, color, isFilled, params[0], params[1], params[2]);
        } else if (type == "line" && params.size() >= 4) {
            newShape = std::make_unique<Line>(nextId++, color, params[0], params[1], params[2], params[3]);
        } else if (type == "triangle" && params.size() >= 3) {
            newShape = std::make_unique<Triangle>(nextId++, color, isFilled, params[0], params[1], params[2]);
        }
        
        if (newShape) {
            shapes.push_back(std::move(newShape));
            std::cout << "shape added with id " << (nextId - 1) << "\n";
        } else {
            std::cout << "error: invalid shape parameters or type\n";
        }
    }
};

#endif // SHAPE_MANAGER_H
