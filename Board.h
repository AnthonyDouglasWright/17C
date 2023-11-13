/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Board.h
 * Author: aawri
 *
 * Created on October 11, 2023, 8:07 PM
 */

#ifndef BOARD_H
#define BOARD_H
#include <unordered_map>
#include <list>
#include <iostream>
#include "Ships.h"
class Board {
public:
    Board();
    void resetBoard();
    void printBoard();
    bool * hitCheck(char, char);
    bool alreadyChecked(char, char );
    void markBoard(bool, char , char);
    int convertPostion(char);
    bool addShipPostion(char *, char *, int size, int id);
    void addShips(int, int);
    
private:
    char ** playerBoard;
    int size = 10;
    std::unordered_map<char, std::unordered_map<char, int>> playerShipPostion;
    std::unordered_map<int, Ships> playerShips;
};

#endif /* BOARD_H */

