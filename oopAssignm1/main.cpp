//
//  main.cpp
//  oopAssignm1
//
//  Created by Maria Goncharuk on 19.09.2026.
//

#include <iostream>
#include "Board.h"

int main() {
    Board board;
    board.setPixel(0, 0, '*');
    board.setPixel(79, 24, '#');
    board.setPixel(40, 12, '0');
    board.setPixel(100, 10, 'x');
    board.print();
    return 0;
    
    shapeMahager b;
    
}
