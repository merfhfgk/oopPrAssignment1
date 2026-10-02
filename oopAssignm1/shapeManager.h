//
//  shapeManager.h
//  oopAssignm1
//
//  Created by Maria Goncharuk on 30.10.2026.
//

#ifndef SHAPE_MANAGER_H
#define SHAPE_MANAGER_H

#include "Board.h"
#include "Shape.h"
#include "Shapes.h"
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
    
    int findIndexById(int id) const {
        for (size_t i = 0; i < shapes.size(); ++i) {
            if (shapes[i]->getId() == id) return (int)i;
        }
        return -1;
    }
    std::unique_ptr<Shape> createShape(int id, const std::string& type, const std::string& color,
                                           bool isFilled, const std::vector<int>& p) const {
        for (int v : p) {
            if (v > 10000 || v < -10000) return nullptr;   // захист від переповнення
        }
        std::unique_ptr<Shape> shape;
        if (type == "box" && p.size() == 4) {
            shape = std::make_unique<Box>(id, color, isFilled, p[0], p[1], p[2], p[3]);
        } else if (type == "circle" && p.size() == 3) {
            shape = std::make_unique<Circle>(id, color, isFilled, p[0], p[1], p[2]);
        } else if (type == "line" && p.size() == 4) {
            shape = std::make_unique<Line>(id, color, isFilled, p[0], p[1], p[2], p[3]);
        } else if (type == "triangle" && p.size() == 3) {
            shape = std::make_unique<Triangle>(id, color, isFilled, p[0], p[1], p[2]);
        }
        if (shape && !shape->isValid()) shape = nullptr;
        return shape;
    }
    std::string checkPlacement(const Shape& s, int ignoreId,
    const std::vector<std::unique_ptr<Shape>>& list) const {
        Rect r = s.getBounds();
        bool tooBig = (r.right - r.left + 1 > board.getWidth()) || (r.bottom - r.top + 1 > board.getHeight());
        bool outside = (r.right < 0 || r.bottom < 0 || r.left >= board.getWidth() || r.top >= board.getHeight());
        if (tooBig || outside) return "error: shape will go out of the board";
        for (const auto& other : list) {
            if (other->getId() != ignoreId && other->sameAs(s)) {
                return "error: the same shape already exists";
            }
        }
        return "";
    }
    
    bool parseLine(const std::string& line, std::unique_ptr<Shape>& result) const {
        std::stringstream ss(line);
        int id;
        std::string type, mode, color;
        if (!(ss >> id >> type >> mode >> color)) return false;
        if (id <= 0 || (mode != "fill" && mode != "frame")) return false;
     
        std::vector<int> params;
        int p;
        while (ss >> p) params.push_back(p);
        if (!ss.eof()) return false;   // в кінці рядка лишилось щось не число
    
        result = createShape(id, type, color, mode == "fill", params);
        return result != nullptr;
    }
    
public:
    void drawBoard() {
        board.clear();
        for (auto& s : shapes) {
            s->draw(board);
        }
        board.print();
    }
    
    void printAvailableShapes() const {
        std::cout << "box <x> <y> <width> <height>\n";
        std::cout << "circle <x> <y> <radius>\n";
        std::cout << "line <x1> <y1> <x2> <y2>\n";
        std::cout << "triangle <x> <y> <height>\n";
        std::cout << "usage: add <shape> fill|frame <color> <params>\n";
    }
    
    void addShape(const std::string& type, const std::string& color, bool isFilled, const std::vector<int>& params) {
        std::unique_ptr<Shape> newShape = createShape(nextId, type, color, isFilled, params);
        if (!newShape) {
            std::cout << "error: invalid shape parameters or type\n";
            return;
        }
        std::string error = checkPlacement(*newShape, -1, shapes);
        if (!error.empty()) {
            std::cout << error << "\n";
            return;
        }
        std::cout << newShape->getInfo() << "\n";
        shapes.push_back(std::move(newShape));
        nextId++;
    }
     
    void listShapes () const {
        if (shapes.empty()) {
            std::cout << "No shapes on board\n";
            return;
        }
        for (const auto& s : shapes) {
            std::cout << s->getInfo() << "\n";
        }
    }
    
    void selectById(int id) {
        int index = findIndexById(id);
        if (index != -1){
            selectedId = id;
            std::cout << shapes[index]->getInfo() << "\n";
        } else {
            selectedId = -1;
            std::cout << "Shape wasn't found\n";
        }
    }
    
    void selectByCoordinates(int px, int py) {
        for (int i = (int)shapes.size() - 1; i >= 0; --i) {
            if (shapes[i]->contains(px, py)) {
                selectedId = shapes[i]->getId();
                std::cout << shapes[i]->getInfo() << "\n";
                return;
            }
        }
        selectedId = -1;
        std::cout << "Shape wasn't found\n";
    }
    
    void removeSelected(){
        int index = findIndexById(selectedId);
        if (index == -1) {
            std::cout << "Error: no shape was selected\n";
            return;
        }
        std::cout << shapes[index]->getId() << " " << shapes[index]->getName() << " removed\n";
        shapes.erase(shapes.begin() + index);
        selectedId = -1;
    }
    
    void clearAll(){
        shapes.clear();
        board.clear();
        selectedId = -1;
        std::cout << "Board is clear\n";
    }
    
    void editSelected(const std::vector<int>& params) {
        int index = findIndexById(selectedId);
        if (index == -1) {
            std::cout << "error: no shape was selected\n";
            return;
        }
        if ((int)params.size() != shapes[index]->getEditParamCount()) {
            std::cout << "error: invalid argument count\n";
            return;
        }
        std::unique_ptr<Shape> copy = shapes[index]->clone();
        copy->edit(params);
        if (!copy->isValid()) {
            std::cout << "error: invalid argument\n";
            return;
        }
        std::string error = checkPlacement(*copy, selectedId, shapes);
        if (!error.empty()) {
            std::cout << error << "\n";
            return;
        }
        std::cout << "size of " << copy->getName() << " changed\n";
        shapes[index] = std::move(copy);
    }
    
    void paintSelected(const string& newColor) {
        Shape* sh = findShapeBuId(selectedId);
        if (!sh) {
            cout << "Error: no shape selected\n";
            return;
        }
        s->setColor(newColor);
        cout << "Shape painted to " << newColor << "\n";
    }
    
    void saveToFile(const string& filepath) const {
        ofstream outFile(filepath);
        if (!outFile.is_open()) {
            cout << "Error: could not open file for writing\n";
            return;
        }
        for (const auto& s : shapes) {
            outFile << s->getInfo() << "\n";
        }
        cout << "Board is saved to " << filepath << "\n";
    }
    
    void loadFromFile(const string& filepath) {
        ifstream inFile(filepath);
        if (!inFile.is_open()) {
            cout << "Error: could not open file or file is invalid\n"; //
            return;
        }

        vector<unique_ptr<Shape>> tempShapes;
        string line;
        int maxId = 0;

        while (getline(inFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            int id;
            string type, color, modeOrParam;
            ss >> id >> type >> color;
            
            if (id > maxId) maxId = id;
            if (type == "box") {
                string mode;
                ss >> mode;
                bool fill = (mode == "fill");
                int x, y, w, h;
                ss >> x >> y >> w >> h;
                tempShapes.push_back(make_unique<Box>(id, color, fill, x, y, w, h));
            } else if (type == "circle") {
                string mode;
                ss >> mode;
                bool fill = (mode == "fill");
                int cx, cy, r;
                ss >> cx >> cy >> r;
                tempShapes.push_back(make_unique<Circle>(id, color, fill, cx, cy, r));
            } else if (type == "line") {
                int x1, y1, x2, y2;
                ss >> x1 >> y1 >> x2 >> y2;
                tempShapes.push_back(make_unique<Line>(id, color, x1, y1, x2, y2));
            } else if (type == "triangle") {
                string mode;
                ss >> mode;
                bool fill = (mode == "fill");
                int tx, ty, h;
                ss >> tx >> ty >> h;
                tempShapes.push_back(make_unique<Triangle>(id, color, fill, tx, ty, h));
            }
        }
        shapes = move(tempShapes);
        nextId = maxId + 1;
        selectedId = -1;
        cout << "board is loaded from " << filepath << "\n";
    }
};

#endif // SHAPE_MANAGER_H
