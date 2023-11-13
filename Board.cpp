/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Board.cpp
 * Author: aawri
 * 
 * Created on October 11, 2023, 8:07 PM
 */

#include "Board.h"
Board::Board() {
    size = 10;
    playerBoard = new char*[size];
    for(int i = 0; i < size; i++){
        playerBoard[i]  = new char[size];
        for(int j = 0; j< size; j++){
            playerBoard[i][j] = 'x';
        }
    }
}


void Board::resetBoard(){
    for(int i = 0; i < size; i++){
     for(int j = 0; j< size; j++){
         playerBoard[i][j] = 'x';
     }
}
    playerShipPostion.clear();
    playerShips.clear();
}
 bool Board::alreadyChecked(char pX, char pY){
    int x = this->convertPostion(pX);
    int y = this->convertPostion(pY);
    if(playerBoard[y][x] != 'x'){
        return true;
    }
    return false;
 }
 
bool * Board::hitCheck(char pX, char pY){
    bool * checks = new bool[2];
    bool hit = playerShipPostion[pX][pY] > 0;
    checks[0] = hit;
    if(hit){
       playerShips[playerShipPostion[pX][pY]].hits +=1;
       playerShips[playerShipPostion[pX][pY]].hits >= playerShips[playerShipPostion[pX][pY]].length ? checks[1] = true: checks[1] = false;
    }
    else{
        checks[1] = false;
    }
    return checks;
}

int Board::convertPostion(char p){
    if(p >= 'A' && p <= 'Z'){
        return p - 'A';
    }
    else{
        return p - '0';
    }
}
 
bool Board::addShipPostion(char *pX, char *pY, int size, int id){
    for(int i = 0; i < size; i++){
        if(playerShipPostion[pX[i]][pY[i]] > 0){
            return false;
        }
    }
    for(int i = 0; i < size; i++){
    playerShipPostion[pX[i]][pY[i]] = id;
    }
    return true;
}

void Board::addShips(int id, int length){
    Ships ship; 
    ship.id = id;
    ship.length = length;
    ship.hits = 0;
    playerShips[id] = ship;
}


void Board::markBoard(bool hit, char pX, char pY){
    int x = this->convertPostion(pX);
    int y = this->convertPostion(pY);
   if(hit){       
          playerBoard[y][x] = 'H';
          std::cout << "********************\nShip Hit at "<< pX << pY <<"\n********************\n";
    }
    else{ 
        playerBoard[y][x] = 'O';
        std::cout << "********************\nShip Missed at "<< pX << pY <<"\n********************\n";
    }
    
    
}
    
void Board::printBoard(){
    char row = '@';
    std::cout <<"  0 1 2 3 4 5 6 7 8 9" << std::endl;
    for(int i = 0; i < 10; i++){
        row += 1;
        std::cout << row <<" ";
        for(int j = 0; j < 10; j++){
            std::cout << playerBoard[i][j];
            if(j < 9){
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}