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

int main() {
    ShapeManager manager;
    string commandLine;

    cout << "=== Shapes Blackboard Application ==_\n";
    cout << "Type 'shapes' to see available commands or enter commands below:\n> ";

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
        //else if (cmd == "shapes") {
        //    manager.printAvailableShapes();
        //}
        else if (cmd == "clear") {
            manager.clearAll();
        }
        else if (cmd == "remove") {
            manager.removeSelected();
        }
        else if (cmd == "add") {
            string color, type, modeStr;
            ss >> color >> type;
            
            bool isFilled = false;
            if (type != "line") {
                ss >> modeStr;
                isFilled = (modeStr == "fill");
            }

            vector<int> params;
            int p;
            while (ss >> p) {
                params.push_back(p);
            }
            manager.addShape(type, color, isFilled, params);
        }
        else if (cmd == "select") {
            int arg1, arg2;
            if (ss >> arg1) {
                if (ss >> arg2) {
                    manager.selectByCoordinates(arg1, arg2);
                } else {
                    manager.selectById(arg1);
                }
            }
        }
        else if (cmd == "save") {
            string filepath;
            ss >> filepath;
            manager.saveToFile(filepath);
        }
        else if (cmd == "load") {
            string filepath;
            ss >> filepath;
            manager.loadFromFile(filepath);
        }
        else {
            cout << "Unknown command: " << cmd << "\n";
        }

        cout << "> ";
    }

    return 0;
}

