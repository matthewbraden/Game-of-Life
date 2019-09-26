#include "GameBoard.h"
#include "SpaceType.h"
#include "catch.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

//Template for testing from https://gitlab.cas.mcmaster.ca/smiths/se2aa4_cs2me3/blob/master/Assignments/A3/A3Soln/implementation/test/testGameBoard.cpp

/**
 * @file    testGameBoard.cpp
 * @author  Matthew Braden
 * @brief   Test modules for the game board
 * @date    April 6th 2019
 */

std::vector< std::vector <OccupancyT> > new_board(){
    std::vector< std::vector <OccupancyT> > z;
    for (unsigned int i = 0; i < ROWS; i++) {
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
    return z;
}

std::vector< std::vector <OccupancyT> > too_small(){
    std::vector< std::vector <OccupancyT> > z;
    for (unsigned int i = 0; i < ROWS; i++) {
        for (unsigned int j = 0; j < 8; j++) {
            unsigned int a = rand() % 1;
            if (a == 0){
                z[i][j] = Full;
            }
            else if (a == 1){
                z[i][j] = Empty;
            }
        }
    }
    return z;
}

TEST_CASE("tests for GameBoard", "[GameBoard]"){
    
    SECTION ("test for constructor size"){
        BoardT board(new_board());
        REQUIRE(board[0].size() == 10);
        REQUIRE(board.size() == 10);
    }

    SECTION ("test for is valid replace empty throws exception"){
        BoardT board(new_board());
        REQUIRE_THROWS_AS(board.is_valid_replace_empty(Empty, 13, 7), std::out_of_range);
        REQUIRE_THROWS_AS(board.is_valid_replace_empty(Empty, 2, -1), std::out_of_range);
        REQUIRE_THROWS_AS(board.is_valid_replace_empty(Full, -34, 32), std::out_of_range);
    }

    SECTION("test for is valid replace empty"){
        BoardT board(new_board());
        unsigned int m = 0;
        unsigned int n = 0;
        for (unsigned int i = 0; i < ROWS; i++) {
            for (unsigned int j = 0; j < COLUMNS; j++){
                if (board.is_valid_replace_empty(Empty, i, j) || board.is_valid_replace_empty(Full, i, j)){
                    m = i;
                    n = j;
                    break;
                }
            }
        }
        REQUIRE(board.is_valid_replace(Empty, m, n) || board.is_valid_replace(Full, m, n));
    }

    SECTION ("test for is valid replace full throws exception"){
        BoardT board(new_board());
        REQUIRE_THROWS_AS(board.is_valid_replace_full(Empty, 13, 7), std::out_of_range);
        REQUIRE_THROWS_AS(board.is_valid_replace_full(Empty, 2, -1), std::out_of_range);
        REQUIRE_THROWS_AS(board.is_valid_replace_full(Full, -34, 32), std::out_of_range);
    }

    SECTION("test for is valid replace full"){
        BoardT board(new_board());
        unsigned int m = 0;
        unsigned int n = 0;
        for (unsigned int i = 0; i < ROWS; i++) {
            for (unsigned int j = 0; j < COLUMNS; j++){
                if (board.is_valid_replace_full(Empty, i, j) || board.is_valid_replace_full(Full, i, j)){
                    m = i;
                    n = j;
                    break;
                }
            }
        }
        REQUIRE(board.is_valid_full(Empty, m, n) || board.is_valid_full(Full, m, n));
    }

    SECTION ("test for is populated throws exception"){
        BoardT board(new_board());
        REQUIRE_THROWS_AS(board.is_populated(15, 2), std::out_of_range);
        REQUIRE_THROWS_AS(board.is_populated(5, -3), std::out_of_range);
        REQUIRE_THROWS_AS(board.is_populated(-5, 20), std::out_of_range);
    }

    SECTION("test for is populated"){
        BoardT board(new_board());
        unsigned int m = 0;
        unsigned int n = 0;
        for (unsigned int i = 0; i < ROWS; i++) {
            for (unsigned int j = 0; j < COLUMNS; j++){
                if (board.is_populated(i, j)){
                    m = i;
                    n = j;
                    break;
                }
            }
        }
        REQUIRE(board.is_populated(m, n));
    }

    SECTION ("test for replace all throws exception"){
        BoardT board(too_small());
        REQUIRE_THROWS_AS(board.replace_all(), std::invalid_argument);
        REQUIRE_THROWS_AS(board.replace_all(), std::invalid_argument);
        REQUIRE_THROWS_AS(board.replace_all(), std::invalid_argument);
    }

    SECTION("test for valid replace exists"){
        BoardT board(new_board());
        REQUIRE(board.valid_replace_exists(Full);
        REQUIRE(board.valid_replace_exists(Empty));
    }

    SECTION("test for is game over"){
        BoardT board(new_board());
        if (valid_replace_exists(Full) || valid_replace_exists(Empty)){
            REQUIRE(!is_game_over());
        }
        REQUIRE(is_game_over());
    }
    
}
