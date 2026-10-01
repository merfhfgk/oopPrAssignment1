//
//  BOARD.h
//  oopAssignm1
//
//  Created by Maria Goncharuk on 18.09.2026.
//
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>


class Board {
private:
    int width;
    int height;
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<int>> colors;
public:
    Board(int w = 80, int h = 25) : width(w), height(h){
        clear();
    }
    void clear(){
        grid.assign(height, std::vector<char>(width, ' '));
        colors.assign(height, std::vector<int>(width, 0));
    }
    void print() const{
        for (int y = 0; y < height; y++){
            int current = 0;
            for (int x = 0; x < width; x++){
                if (grid[y][x] != ' ' && colors[y][x] != current) {
                    current = colors[y][x];
                    std::cout << "\033[" << current << "m";
                }
                std::cout << grid[y][x];
            }
            if (current != 0) std::cout << "\033[0m";
            std::cout << '\n';
        }
    }
    
    void setPixel(int x, int y, char c, int colorCode = 0) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x]=c;
            colors[y][x] = colorCode;
        }
    }

    int getWidth() const {return width;}
    int getHeight() const {return height; }
};


#endif // BOARD_H
