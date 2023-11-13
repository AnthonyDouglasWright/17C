/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Game.h
 * Author: aawri
 *
 * Created on October 29, 2023, 1:33 PM
 */

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <list>
#include <utility>
#include "shipTypes.h"
#include "Player.h"
#include "AI.h"

class Game {
public:
    Game();
    void start();
    void end();
    bool endgame();
    void nextTurn();
    void takeTurn(Player *, Player *);
    void aiTurn(Player *, Player *);
    char playerInputCheck();
    void reset();
    
private:
    Player * p1;
    Player * p2;
    Player ** pTurn;
    AI * computer;
    int currentTurn;
    int turnCount;
    int winner;
    std::list<ShipTypes> sTypes;
    
};

#endif /* GAME_H */

