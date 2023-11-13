/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Player.h
 * Author: aawri
 *
 * Created on October 29, 2023, 1:33 PM
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <cstdlib>
#include <ctime>
#include "Board.h"
class Player {
public:
    Player();
    void addShip(int, int);
    void printBoard();
    void reset();
    void sunk();
    void destroyed();
    int getSunk();
    int getDestroyed();
    bool isAI();
    void setAI(int);
    void aiAddShip(int, int);
    int randNum();
    void markShot(char, char, bool);
    bool * takeDamage(char , char );
    bool alreadyChecked(char, char );
    char playerInputCheck();
private:
    bool ai;
    Board * pBoard;
    int shipCount;
    int shipsSunk;
    

};

#endif /* PLAYER_H */

