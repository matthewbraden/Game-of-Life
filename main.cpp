#include <iostream>
#include "SpaceType.h"
#include "GameBoard.h"
#include <vector>
#include <string>
#include <algorithm>

/**
 * @file    main.cpp
 * @brief   Implements the main function
 * @author  Matthew Braden, bradenm, 400109876
 * @date    April 6th 2019
 */

int main(){
    std::vector< std::vector <OccupancyT> > z;
    z.resize(ROWS);
    for (unsigned int i = 0; i < ROWS; i++) {
        z[i].resize(COLUMNS);
        for (unsigned int j = 0; j < COLUMNS; j++) {
            unsigned int a = rand() % 1;
            if (a == 0){
                z[i][j] = Full;
            }
            else if (a == 1){
                z[i][j] = Empty;
            }
        }
    }

    BoardT board(z);

    std::cout << "Does the empty space stay empty" << board.is_valid_replace_empty(Empty, 5, 6) << std::endl;
    std::cout << "Is there a valid move that replaces a full space with an empty space" << board.is_valid_replace_empty(Full, 5, 6) << std::endl;
    std::cout << "Is there a valid move that replaces an empty space with a full space" << board.is_valid_replace_full(Empty, 5, 6) << std::endl;
    std::cout << "Does the full space stay full" << board.is_valid_replace_full(Full, 5, 6) << std::endl;
    std::cout << "Is the space full" << board.is_populated() << std::endl;
    std::cout << "Is there a valid replace empty" << board.valid_replace_exists(Empty) << std::endl;
    std::cout << "Is there a valid replace full" << board.valid_replace_exists(Full) << std::endl;
    std::cout << "Is the game finished" << board.is_game_over() << std::endl;

    for (unsigned int i = 0; i < ROWS; i++){
        for (unsigned int j = 0; j < COLUMNS; j++){
            std::cout << "The " << i << "and" << j << "value is " << z[i][j] << std::endl;
        }
    }

    return 0;
}
