/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Game.cpp
 * Author: aawri
 * 
 * Created on October 29, 2023, 1:33 PM
 */

#include "Game.h"
Game::Game() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    ShipTypes ship1 = { 1, 5, "Carrier"};
    sTypes.push_back(ship1);
    ShipTypes ship2 = { 2, 4, "Battleship"};
    sTypes.push_back(ship2);
    ShipTypes ship3 = { 3, 3, "Cruiser"};
    sTypes.push_back(ship3);
    ShipTypes ship4 = { 4, 3, "Submarine"};
    sTypes.push_back(ship4);
    ShipTypes ship5 = { 5, 2, "Destroyer"};
    sTypes.push_back(ship5);
    p1 = new Player;
    p2 = new Player;
    pTurn = new Player*[2];
    pTurn[0] = p1;
    pTurn[1] = p2;
    computer = new AI();
    
}


void Game::start(){
    int choice;
//    std::cout <<"Is Player 1 an AI?/nYes(1) no(0):";
//    std::cin>>choice;
    std::cout <<"Is Player 1 a Player:";
    p1->setAI(0);
    std::cout <<"Is Player 2 an AI?/nYes(1) no(0):";
    std::cin>>choice;
    p2->setAI(choice);
    std:: cout<<p1->isAI()<< " " << p2->isAI();
    for (auto it = sTypes.begin(); it != sTypes.end(); ++it){
        std::cout <<"Player 1 please place your " << it->name << std::endl;
        p1->isAI()? p1->aiAddShip(it->id,it->length): p1->addShip(it->id,it->length);
        std::cout <<"Player 2 please place your " << it->name << std::endl;
        p2->isAI()? p2->aiAddShip(it->id,it->length): p2->addShip(it->id,it->length);
    }
    currentTurn = 0;
    turnCount = 0;
    nextTurn();
}

void Game::nextTurn(){
    std::cout << "\nTURN " << turnCount/2 << "\n";
    if(!pTurn[currentTurn]->isAI()){
     if(currentTurn ==0 ){
        takeTurn(pTurn[currentTurn],pTurn[currentTurn+1]);
        }
     else{
         takeTurn(pTurn[currentTurn],pTurn[currentTurn-1]);
     }
    }else{
      if(currentTurn ==0 ){
        aiTurn(pTurn[currentTurn],pTurn[currentTurn+1]);
        }
     else{
         aiTurn(pTurn[currentTurn],pTurn[currentTurn-1]);
     }}
    currentTurn = (currentTurn== 0) ? 1 : 0;
    turnCount++;
    if(endgame()) end();
    else  nextTurn();
}

bool Game::endgame(){
    if(p1->getDestroyed() == 0){
        winner = 1;
        return true;
    }
    else if(p2->getDestroyed() == 0){
        winner = 2;
        return true;
    }
    return false;
}

void Game::end(){
    std::cout << "Player " << winner << " won in " << turnCount/2 <<" turns\n";
    std::cout << "Do you wish to play agian(press 1)\nto close press any other key";
    int choice;
    std::cin >>choice;
    if(choice == 1) reset();
}

void Game::reset(){
    
}

void Game::takeTurn(Player* play, Player* op){
    bool turndone = false;
    while(!turndone){
        std::cout << "****Player " << currentTurn+1 << " Turn*****\n";
        play->printBoard();
         char x, y;
         std::cout<<"Enter the Coordinate you wish to fire at\nX Coordinate values are 0 - 9  \nYCoordinate Values are A - J \n ";
         std::cout<<"X: ";
         x = playerInputCheck();
         std::cout<<"Y: ";
         y = playerInputCheck();
         //need to pass pointer of player 
         if(play->alreadyChecked(x, y)){
             std::cout <<"You have Already Choosen That location\nPlease Choose another\n";
         }
         else{
            turndone = true;
            bool * hit = op->takeDamage(x, y);
            play->markShot(x,y, hit[0] );
            if(hit[1]){
                std::cout << "Ship Sunk!\n";
                play->sunk();
                op->destroyed();
            }}
         std::cout << "\n***************************************\n";
    }}

void Game::aiTurn(Player* play, Player* op){
     bool turndone = false;
    while(!turndone){
    std::cout << "****Player " << currentTurn+1 << " Turn*****\n";
    std::pair<char,char> select;
    play->printBoard();
    if(computer->getFind())select = computer->seekAndDestroy();
    else select = computer->searchBlock(); 
     if(play->alreadyChecked(select.first, select.second)){
         std::cout << "That move" << select.first << " " << select.second << " has already been tried" << std::endl;
     }
     else{
        turndone = true;
        bool * hit = op->takeDamage(select.first, select.second);
        std::cout <<" Ship Hit? " << hit[0] << " sunk? " << hit[1] << std::endl; 
        play->markShot( select.first, select.second, hit[0] );
        std::cout <<" Mark Shot" << std::endl; 
        if(hit[0])computer->lastChoiceHit();
        std::cout << "SUNK?" << hit[1] << std::endl;
        if(hit[1]){
            std::cout << "Ship Sunk!\n";
            computer->sunk();
            play->sunk();
            op->destroyed();
        }
        delete[] hit;
     }
    }
     
}

     char Game::playerInputCheck(){
         char input;
         std::cin >> input;
         if((input < 'A' && input > 'J') || (input < '0' && input > '9' )){
             std::cout << "Invalid Coordinate Value\nPlease Choose Again\n";
             return playerInputCheck();
         }
         return input;
     }