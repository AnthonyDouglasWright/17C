/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Player.cpp
 * Author: aawri
 * 
 * Created on October 29, 2023, 1:33 PM
 */

#include "Player.h"

Player::Player() {
    pBoard  = new Board;
    shipCount = 5;
    shipsSunk = 0;
}

void Player::reset(){
    pBoard->resetBoard();
    shipCount = 5;
    shipsSunk = 0;
}

 void Player::addShip(int id, int length){
     std::cout << "Valid Ship placements are Horizontal or Vertical no Diagonal values\nX Coordinate values are A - J \nYCoordinate Values are 0 - 9 \n";
     char * x = new char[length];
     char * y = new char[length];
     bool pass;
     int i = 0;
     while(i < length){
     std::cout <<"Please enter a value for the X Coordinate for the " << i <<" postion:";
     x[i] = playerInputCheck();
     std::cout <<"Please enter a value for the Y Coordinate for the " << i <<" postion:";
     y[i] = playerInputCheck();
     i++;
     }   
     pass = pBoard->addShipPostion(x, y, length, id);
     if(!pass){
         std::cout<< "Invalid Postion Choice\n";
         addShip(id, length);
     }
     pBoard->addShips(id, length);
 }
  char Player::playerInputCheck(){
         char input;
         std::cin.ignore();
         std::cin >> input;
         if((input < 'A' && input > 'J') || (input < '0' && input > '9' )){
             std::cout << "Invalid Coordinate Value\nPlease Choose Again\n";
             return playerInputCheck();
         }
         return input;
     }
 
 bool * Player::takeDamage(char x, char y){
     return pBoard->hitCheck(x,y);
 }

 
 void Player::markShot(char x, char y, bool hit){
      pBoard->markBoard(hit, x , y);
 }
void Player::printBoard(){
    pBoard->printBoard();
}


int Player::getSunk(){
    return shipsSunk;
}
void Player::sunk(){
    shipsSunk++;
}
void Player::destroyed(){
    shipCount--;
}
int Player::getDestroyed(){
    return shipCount;
}
  
bool Player::isAI(){
    return ai;
}

void Player::setAI(int n){
    if(n == 1) ai = true;
    else if(n == 0) ai = false;
    else{
        std::cout<<"It looks like you can't be trusted to make a valid choice!\nI think it would be best if the computer took it from here" << std::endl;
        ai = true;
    }
}

void Player::aiAddShip(int id, int length){
     char * x = new char[length];
     char * y = new char[length];
     bool pass;
     bool xOrY;
     x[0] = static_cast<char>('0' + randNum());
     y[0]  = static_cast<char>('A' + randNum());
     xOrY = randNum() %2 == 0;
     int j = 1;
     for(int i = 1; i < length; i++){
     if(xOrY){    
         x[i] = x[0];
         if(y[i-1] == 'J') j = -1;
         y[i] = (char)y[0] + j ;
     }
     else{
         if(x[i-1] == '9') j = -1;
        x[i] = (char)x[0]+ j; 
        y[i] = y[0];
     }
     if(j < 0) j--;
     else j++;
     }
     pass = pBoard->addShipPostion(x, y, length, id);
     if(!pass) aiAddShip(id, length);
     else pBoard->addShips(id, length);
}


int Player::randNum(){
    //std::srand(static_cast<unsigned int>(std::time(nullptr)));
    return std::rand() % 10;
}

bool Player::alreadyChecked(char x, char y){
    return pBoard->alreadyChecked(x, y);
}