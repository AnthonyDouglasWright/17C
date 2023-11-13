/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   AI.h
 * Author: aawri
 *
 * Created on October 29, 2023, 1:34 PM
 */

#ifndef AI_H
#define AI_H
#include "Block.h"
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <queue>
#include <deque>
#include <algorithm>
#include <random>

class AI {
public:
    AI();
    std::pair<char, char> searchBlock();  
    std::pair<char, char> seekAndDestroy();
    std::pair<char, char> randChar();
    void createQueue();
    void clearQueue();
    bool getFind();
    void lastChoiceHit();
    void sunk();
    
private:
    bool stop;
    std::mt19937 gen();
    Block * headBlock;
    Block * currentBlock;
    std::pair<char, char> lastChoice;
    std::pair<char, char> initialHit;
    bool lastSearch;
    bool reset;
    std::queue<std::pair<char,char>> seek;
};

#endif /* AI_H */

