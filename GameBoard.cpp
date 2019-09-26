#include <algorithm>
#include <iostream>
#include "GameBoard.h"
#include "SpaceType.h"
#include <vector>
#include <string>

/**
 * @file    GameBoard.cpp
 * @brief   Implements functions from GameBoard.h
 * @author  Matthew Braden, bradenm, 400109876
 * @date    April 6th 2019
 */

/**
 * @brief           Initializes the game board
 * @details         Function that creates and fills in the game board
 * @param options   This is a multidimensional vector that contains values of different states
 */ 
BoardT::BoardT(std::vector< std::vector <OccupancyT> > options){
    if ((A.size() != ROWS) && (A[0].size() != COLUMNS)){
        throw std::invalid_argument("Cannot form the game board");
    }
    char a = static_cast<char>(Full);   // Converting into ASCII characters
    char b = static_cast<char>(Empty); // Initializing the game board
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLUMNS; j++){
            if (options[i][j] == Full){
                this->A[i][j] = a; 
            }
            else if (options[i][j] == Empty){
                this->A[i][j] = b;
            }
        }
    }
}

/**
 * @brief       Checks for empty move
 * @details     Function that makes sure if a spot of the game board can be empty
 * @param c     A type of enum OccupancyT from SpaceType.h
 * @param nx    Row coordinate in the vector A
 * @param ny    Column coordinate in the vector A
 */
bool BoardT::is_valid_replace_empty(OccupancyT c, unsigned int nx, unsigned int ny){
    if ((nx > 9) || (nx < 0) || (ny > 9) || (ny < 0)){
        throw std::out_of_range("Cannot replace with empty");
    }
    else if (c == Empty){   // Checks on the type of OccupancyT
        return valid_empty_empty(nx, ny);
    }
    else if (c == Full){
        return valid_empty_full(nx, ny);
    }
    return false;
}

/**
 * @brief       Checks for full move
 * @details     Function that makes sure if a spot of the game board can be filled
 * @param c     A type of enum OccupancyT from SpaceType.h
 * @param nx    Row coordinate in the vector A
 * @param ny    Column coordinate in the vector A
 */
bool BoardT::is_valid_replace_full(OccupancyT c, unsigned int nx, unsigned int ny){
    if ((nx > 9) || (nx < 0) || (ny > 9) || (ny < 0)){
        throw std::out_of_range("Cannot replace with full");
    }
    else if (c == Empty){   // Checks on the type of OccupancyT
        return valid_full_empty(nx, ny);
    }
    else if (c == Full){
        return valid_full_full(nx, ny);
    }
    return false;
}

/**
 * @brief       Checks if space is filled
 * @details     Function that checks if a certain space on the board is empty of full
 * @param nx    Row coordinate in the vector A       
 * @param ny    Colunn coordinate in the vector A
 */
bool BoardT::is_populated(unsigned int nx, unsigned int ny){
    char a = static_cast<char>(Full);
    char b = static_cast<char>(Empty);
    if ((nx > 9) || (nx < 0) || (ny > 9) || (ny < 0)){
        throw std::out_of_range("Out of range of game board");
    }
    else if (A[nx][ny] == a){   // Checks if the space has the value of Full
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief   Replaces space with empty or full
 * @details Function that replaces a space in the vector with an OccupancyT Empty or Full value 
 */ 
void BoardT::replace_all(){
    if ((A.size() != ROWS) && (A[0].size() != COLUMNS)){
        throw std::invalid_argument("Cannot make empty move");
    }
    std::vector< std::vector <char> > temp; //temp vector needed so that we can store a new vector without getting wrong values
    char a = static_cast<char>(Full);
    char b = static_cast<char>(Empty);
    temp.resize(ROWS);
    for (unsigned int i = 0; i < ROWS; i++){
        temp[i].resize(COLUMNS);
        for (unsigned int j = 0; j < COLUMNS; j++){
            if (is_valid_replace_empty(Empty, i, j) || is_valid_replace_empty(Full, i, j)){
                temp[i][j] = b; // Replaces with empty
            }
            else if (is_valid_replace_full(Full, i, j) || is_valid_replace_full(Empty, i, j)){
                temp[i][j] = a; // Replaces with full
            }
        }
    }
    A = temp;
}

/**
 * @brief   Checks if a replace can happen
 * @details Function that iterates through the vector A and checks if any space can be replaced
 * @param c A type of enum OccupancyT from SpaceType.h
 */ 
bool BoardT::valid_replace_exists(OccupancyT c){
    unsigned int count = 0;
    for (unsigned int i = 0; i < ROWS; i++){
        for (unsigned int j = 0; j < COLUMNS; j++){
            if (is_valid_replace_full(c, i, j) || is_valid_replace_empty(c, i, j)){
                return true;    // Checks if a replace move can occur wether it is empty of full
            }
        }
    }
    return false;
}

/**
 * @brief   Checks if the game is over
 * @details Function that checks if there are any possible moves that can occur, if there are none it returns true
 */ 
bool BoardT::is_game_over(){
    if (valid_replace_exists(Empty) || valid_replace_exists(Full)){
        return false;   // Checks if there are no moves left to make
    }
    else{
        return true;
    }
}

/**
 * @brief   Shows the game board
 * @details Function that returns the game board
 */ 
std::vector< std::vector <char> > BoardT::toSeq(){
    return A; // Returns the vector of the game board
}

/**
 * @brief       Checks if empty to full
 * @details     Function that checks if an empty space can become a full space
 * @param nx    Row coordinate in the vector A
 * @param ny    Column coordinate in the vector A
 */ 
bool BoardT::valid_empty_full(unsigned int nx, unsigned int ny){
    char a = static_cast<char>(Full);
    char b = static_cast<char>(Empty);
    unsigned int count = 0;
    if ((nx == 0) && !((ny == 0) || (ny == 9))){
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }                           // Checks the top row of the board
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if (count == 3){
            return true;
        } 
    }
    else if ((nx == 9) && !((ny == 0) || (ny == 9))){
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx-1][ny-1] == a){
            count++;
        }                           // Checks the bottom row of the board
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if (count == 3){
            return true;
        } 
    }
    else if ((ny == 0) && !((nx == 0) || (nx == 9))){
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx-1][ny+1] == a){
            count++;
        }                           // Checks the left column of the board
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if (count == 3){
            return true;
        } 
    }
    else if ((ny == 9) && !((nx == 0) || (nx == 9))){
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx-1][ny-1] == a){
            count++;
        }                           // Checks the right column of the board
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if (count == 3){
            return true;
        } 
    }
    else if ((nx == 0) && (ny == 0)){
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }                           // Checks the top left spot
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if (count == 3){
            return true;
        } 
    }
    else if ((nx == 0) && (ny == 9)){
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }                           // Checks the top right spot
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if (count == 3){
            return true;
        } 
    }
    else if ((nx == 9) && (ny == 0)){
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }                           // Checks the bottom left spot
        if (A[nx][ny+1] == a){
            count++;
        }
        if (count == 3){
            return true;
        } 
    }
    else if ((nx == 9) && (ny == 9)){
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }                               // Checks the bottom right spot
        if (A[nx][ny-1] == a){
            count++;
        }
        if (count == 3){
            return true;
        } 
    }
    else if ((ny != 0) && (ny != 9) && (nx != 0) && (nx != 9)){
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx-1][ny+1] == a){
            count++;
        }                               // Checks a regular spot on the board
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if (count == 3){
            return true;
        } 
    }
    return false;
}

/**
 * @brief       Checks if empty to empty
 * @details     Function that checks if an empty space can stay empty
 * @param nx    Row coordinate in the vector A
 * @param ny    Column coordinate in the vector A
 */ 
bool BoardT::valid_empty_empty(unsigned int nx, unsigned int ny){
    char a = static_cast<char>(Full);
    char b = static_cast<char>(Empty);
    unsigned int count = 0;
    if ((nx == 0) && !((ny == 0) || (ny == 9))){
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if (count != 3){
            return true;
        } 
    }
    else if ((nx == 9) && !((ny == 0) || (ny == 9))){
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if (count != 3){
            return true;
        } 
    }
    else if ((ny == 0) && !((nx == 0) || (nx == 9))){
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if (count != 3){
            return true;
        } 
    }
    else if ((ny == 9) && !((nx == 0) || (nx == 9))){
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if (count != 3){
            return true;
        } 
    }
    else if ((nx == 0) && (ny == 0)){
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if (count != 3){
            return true;
        } 
    }
    else if ((nx == 0) && (ny == 9)){
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if (count != 3){
            return true;
        } 
    }
    else if ((nx == 9) && (ny == 0)){
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (count != 3){
            return true;
        } 
    }
    else if ((nx == 9) && (ny == 9)){
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx][ny-1] == a){
            count++;
        }
        if (count != 3){
            return true;
        } 
    }
    else if ((ny != 0) && (ny != 9) && (nx != 0) && (nx != 9)){
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if (count != 3){
            return true;
        } 
    }
    return false;
}

/**
 * @brief       Checks if full to empty
 * @details     Function that checks if a full space can become an empty space
 * @param nx    Row coordinate in the vector A
 * @param ny    Column coordinate in the vector A
 */ 
bool BoardT::valid_full_empty(unsigned int nx, unsigned int ny){
    char a = static_cast<char>(Full);
    char b = static_cast<char>(Empty);
    unsigned int count = 0;
    if ((nx == 0) && !((ny == 0) || (ny == 9))){
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if ((count != 2) || (count != 3)){
            return true;
        } 
    }
    else if ((nx == 9) && !((ny == 0) || (ny == 9))){
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if ((count != 2) || (count != 3)){
            return true;
        } 
    }
    else if ((ny == 0) && !((nx == 0) || (nx == 9))){
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if ((count != 2) || (count != 3)){
            return true;
        } 
    }
    else if ((ny == 9) && !((nx == 0) || (nx == 9))){
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if ((count != 2) || (count != 3)){
            return true;
        } 
    }
    else if ((nx == 0) && (ny == 0)){
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if ((count != 2) || (count != 3)){
            return true;
        } 
    }
    else if ((nx == 0) && (ny == 9)){
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if ((count != 2) || (count != 3)){
            return true;
        } 
    }
    else if ((nx == 9) && (ny == 0)){
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if ((count != 2) || (count != 3)){
            return true;
        } 
    }
    else if ((nx == 9) && (ny == 9)){
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx][ny-1] == a){
            count++;
        }
        if ((count != 2) || (count != 3)){
            return true;
        } 
    }
    else if ((ny != 0) && (ny != 9) && (nx != 0) && (nx != 9)){
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if ((count != 2) || (count != 3)){
            return true;
        } 
    }
    return false;
}

/**
 * @brief       Checks if full to full
 * @details     Function that checks if a full space can stay full
 * @param nx    Row coordinate in the vector A
 * @param ny    Column coordinate in the vector A
 */
bool BoardT::valid_full_full(unsigned int nx, unsigned int ny){
    char a = static_cast<char>(Full);
    char b = static_cast<char>(Empty);
    unsigned int count = 0;
    if ((nx == 0) && !((ny == 0) || (ny == 9))){
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if ((count == 2) || (count == 3)){
            return true;
        } 
    }
    else if ((nx == 9) && !((ny == 0) || (ny == 9))){
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if ((count == 2) || (count == 3)){
            return true;
        } 
    }
    else if ((ny == 0) && !((nx == 0) || (nx == 9))){
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if ((count == 2) || (count == 3)){
            return true;
        } 
    }
    else if ((ny == 9) && !((nx == 0) || (nx == 9))){
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if ((count == 2) || (count == 3)){
            return true;
        } 
    }
    else if ((nx == 0) && (ny == 0)){
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if ((count == 2) || (count == 3)){
            return true;
        } 
    }
    else if ((nx == 0) && (ny == 9)){
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if ((count == 2) || (count == 3)){
            return true;
        } 
    }
    else if ((nx == 9) && (ny == 0)){
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if ((count == 2) || (count == 3)){
            return true;
        } 
    }
    else if ((nx == 9) && (ny == 9)){
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx][ny-1] == a){
            count++;
        }
        if ((count == 2) || (count == 3)){
            return true;
        } 
    }
    else if ((ny != 0) && (ny != 9) && (nx != 0) && (nx != 9)){
        if (A[nx-1][ny-1] == a){
            count++;
        }
        if (A[nx-1][ny] == a){
            count++;
        }
        if (A[nx-1][ny+1] == a){
            count++;
        }
        if (A[nx][ny-1] == a){
            count++;
        }
        if (A[nx][ny+1] == a){
            count++;
        }
        if (A[nx+1][ny-1] == a){
            count++;
        }
        if (A[nx+1][ny] == a){
            count++;
        }
        if (A[nx+1][ny+1] == a){
            count++;
        }
        if ((count == 2) || (count == 3)){
            return true;
        } 
    }
    return false;
}