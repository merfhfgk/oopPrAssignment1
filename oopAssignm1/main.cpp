//
//  main.cpp
//  oopAssignm1
//
//  Created by Maria Goncharuk on 19.09.2026.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "ShapeManager.h"

using namespace std;

bool readNumbers(stringstream& ss, vector<int>& numbers) {
    int p;
    while (ss >> p) {
        numbers.push_back(p);
    }
    if (!ss.eof()) {
        cout << "error: invalid argument\n";
        return false;
    }
    return true;
}

int main() {
    ShapeManager manager;
    string commandLine;

    cout << "--- Shapes Blackboard Application ---\n";
    cout << "Type 'shapes' to see available shapes or enter commands below:\n> ";

    while (getline(cin, commandLine)) {
        if (commandLine.empty()) {
            cout << "> ";
            continue;
        }

        stringstream ss(commandLine);
        string cmd;
        ss >> cmd;

        if (cmd == "exit" || cmd == "quit") {
            break;
        }
        else if (cmd == "draw") {
            manager.drawBoard();
        }
        else if (cmd == "list") {
            manager.listShapes();
        }
        else if (cmd == "shapes") {
            manager.printAvailableShapes();
        }
        else if (cmd == "clear") {
            manager.clearAll();
        }
        else if (cmd == "remove") {
            manager.removeSelected();
        }
        else if (cmd == "add") {
            string type, mode, color;
            ss >> type >> mode >> color;

            vector<int> params;
            if (color.empty() || (mode != "fill" && mode != "frame")) {
                cout << "error: usage: add <shape> fill|frame <color> <params>\n";
            } else if (readNumbers(ss, params)) {
                manager.addShape(type, color, mode == "fill", params);
            }
        }
        else if (cmd == "select") {
            vector<int> nums;
            if (readNumbers(ss, nums)) {
                if (nums.size() == 1) {
                    manager.selectById(nums[0]);
                } else if (nums.size() == 2) {
                    manager.selectByCoordinates(nums[0], nums[1]);
                } else {
                    cout << "error: usage: select <id> or select <x> <y>\n";
                }
            }
        }
        else if (cmd == "edit") {
            vector<int> nums;
            if (readNumbers(ss, nums)) {
                manager.editSelected(nums);
            }
        }
        else if (cmd == "paint") {
            string color;
            ss >> color;
            if (color.empty()) {
                cout << "error: usage: paint <color>\n";
            } else {
                manager.paintSelected(color);
            }
        }
        else if (cmd == "move") {
            vector<int> nums;
            if (readNumbers(ss, nums)) {
                if (nums.size() == 2) {
                    manager.moveSelected(nums[0], nums[1]);
                } else {
                    cout << "error: usage: move <x> <y>\n";
                }
            }
        }
        else if (cmd == "save" || cmd == "load") {
            string filepath;
            getline(ss >> ws, filepath);
            if (filepath.empty()) {
                cout << "error: file path is missing\n";
            } else if (cmd == "save") {
                manager.saveToFile(filepath);
            } else {
                manager.loadFromFile(filepath);
            }
        }
        else {
            cout << "Unknown command: " << cmd << "\n";
        }

        cout << ">> ";
    }

    return 0;
}
