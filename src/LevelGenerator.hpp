#ifndef LEVEL_GENERATOR_HPP_
#define LEVEL_GENERATOR_HPP_

#include <iostream>

/*! \brief A class to handle random level generation. */
class LevelGenerator {
   public:
    /*! A method that generates 9 levels of 120 (15x9) tiles each. It does it by first randomly 
    assigning a number to each tile, that corresponds to the tile type, and then setting the 
    doors in the right places to allow correct moving through the rooms of the dungeon. */
    static void GenerateLevel(int (&levels_)[9][120]) {
        srand((unsigned)time(NULL));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 120; j++) {
                levels_[i][j] = 0;
                int random = rand() % 60;
                if (random < 3) {
                    levels_[i][j] = random;
                }
            }
        }
        levels_[0][59] = 3;  // setting doors on each level
        levels_[1][45] = 3;
        levels_[1][59] = 3;
        levels_[2][45] = 3;
        levels_[2][112] = 3;
        levels_[3][59] = 3;
        levels_[4][59] = 3;
        levels_[4][45] = 3;
        levels_[4][112] = 3;
        levels_[5][45] = 3;
        levels_[5][7] = 3;
        levels_[6][59] = 3;
        levels_[7][59] = 3;
        levels_[7][45] = 3;
        levels_[7][7] = 3;
    }
};

#endif  // LEVEL_GENERATOR_HPP_