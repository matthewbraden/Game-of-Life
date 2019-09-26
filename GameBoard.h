/**
 * @file GameBoard.h
 * @author  Matthew Braden
 * @brief   Header file that lists GameBoard
 * @date April 6th 2019
 */
#ifndef A4_GAME_BOARD_H_
#define A4_GAME_BOARD_H_

#include <string>
#include <vector>
#include "SpaceType.h"



class BoardT{
    private:
        std::vector< std::vector <char> > A;
        bool valid_empty_full(unsigned int nx, unsigned int ny);
        bool valid_empty_empty(unsigned int nx, unsigned int ny);
        bool valid_full_empty(unsigned int nx, unsigned int ny);
        bool valid_full_full(unsigned int nx, unsigned int ny);

    public:
        explicit BoardT(std::vector< std::vector <OccupancyT> > options);
        bool is_valid_replace_empty(OccupancyT c, unsigned int nx, unsigned int ny) ;
        bool is_valid_replace_full(OccupancyT c, unsigned int nx, unsigned int ny);
        bool is_populated(unsigned int nx, unsigned int ny);
        void replace_all();
        char get_array();
        bool valid_replace_exists(OccupancyT c);
        bool is_game_over();
        std::vector< std::vector <char> > toSeq();
};


#endif
