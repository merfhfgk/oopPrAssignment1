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
public:
    Board(int w = 80, int h = 25) : width(w), height(h){
        clear();
    }
    void clear(){
        grid.assign(height, std::vector<char>(width, ' '));
    }
    void print() const{
        for (int y = 0; y < height; y++){
            for (int x = 0; x < width; x++) {
                std::cout << grid[y][x];
            }
            std::cout << '\n';
        }
    }
    void setPixel(int x, int y, char c) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x]=c;
        }
    }

    int getWidth() const {return width;}
    int getHeight() const {return height; }
};


#endif // BOARD_H
