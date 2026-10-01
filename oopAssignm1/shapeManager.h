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
            std::cout << "Shape added with id " << (nextId - 1) << "\n";
        } else {
            std::cout << "Error: invalid shape parameters or type\n";
        }
    }
    void listShapes () const {
        if (shape.empty()) {
            std::cout << "No shapes on board\n";
            return;
        }
        for (const auto& s : shapes) {
            std::cout << s->getInfo() << "\n";
        }
    }
    
    void selectById(int id) {
        Shape* sh = findShapeById(id);
        id (sh){
            selectedId == id;
            std::cout << "Selected shape: " << sh->getInfo() << "\n";
        } else {
            selectedId = -1;
            std::cout << "Shape wasn't found\n";
        }
    }
    
    void selectByCoordinates(int px, int py) {
        for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
            if ((*it)->contains(px, py)) {
                selectedId = (*it)->getId();
                std::cout << "Selected shape: " << (*it)->getInfo() << "\n";
                return;
            }
        }
        selectedId = -1;
        std::cout << "Shape " << (*it)->getInfo() << " was not found\n";
    }
    
    void removeSelected(){
        if (selectedId == -1) {
            std::cout << "Error: no shape was selected\n";
            return;
        }
        for (auto it = shapes.begin(); it != shapes.end(); ++it) {
            if ((*it)->getId() == selectedId) {
                std::cout selectedId << " shape removed\n";
                shapes.erase(it);
                selectedId = -1;
                return;
            }
        }
    }
    
    void clearAll(){
        shapes.clear();
        board.clear();
        selectedId = -1;
        std::cout << "Board is clear\n";
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
