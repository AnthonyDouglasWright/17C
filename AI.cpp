/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   AI.cpp
 * Author: aawri
 * 
 * Created on October 29, 2023, 1:34 PM
 */

#include <c++/bits/stl_pair.h>

#include "AI.h"

AI::AI(){
    // 4 quadrent blocks
    int GRID_SIZE = 10;
    std::deque<int>q1;
    std::deque<int>q2;
    std::deque<int>q3;
    std::deque<int>q4;
    
    // Calculate the mid-point.
    int mid = GRID_SIZE / 2;

    // Generate and distribute the grid values into the respective quadrants.
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int value = i * GRID_SIZE + j;  // Generate values from 0 to 99 sequentially.
            if (i < mid && j < mid) {
                q1.push_back(value);
            } else if (i < mid && j >= mid) {
                q2.push_back(value);
            } else if (i >= mid && j < mid) {
                q3.push_back(value);
            } else {
                q4.push_back(value);
            }
        }
    }
    
        std::random_shuffle(q1.begin(), q1.end());
        std::queue<int> quadrant1(q1);
        std::random_shuffle(q2.begin(), q2.end());
        std::queue<int> quadrant2(q2);
       std::random_shuffle(q3.begin(), q3.end());
        std::queue<int> quadrant3(q3);
        std::random_shuffle(q4.begin(), q4.end());
        std::queue<int> quadrant4(q4);
        headBlock = new Block;
        currentBlock = new Block;
        headBlock ->find = false;
        headBlock->q = quadrant1;
        headBlock->prev = NULL;
        currentBlock = headBlock;
        Block * temp = new Block;
        temp ->find = false;
        temp->q= quadrant2;
        temp->prev = currentBlock;
        currentBlock->next = temp;
        currentBlock = temp;
        temp = new Block;
         temp ->find = false;
        temp->q= quadrant3;
        temp->prev = currentBlock;
        currentBlock->next = temp;
        currentBlock = temp;
        temp = new Block;
        temp ->find = false;
        temp->q= quadrant4;
        temp->prev = currentBlock;
        currentBlock->next = temp;
        currentBlock = headBlock;
    }

    
    //Search in blocks of data.
    std::pair<char, char> AI::searchBlock(){ 
        lastChoice = randChar();
        if(currentBlock->next != NULL){
            currentBlock = currentBlock->next;
        }
        else{
            currentBlock = headBlock;
        }
         std::cout<< "Last Choice Search " << lastChoice.first << " " << lastChoice.second  << std::endl;
        return lastChoice;
    }
        // Generate Char between the values
    std::pair<char, char> AI::randChar(){
        std::pair<char,char> rchar;
        int i = 0;
        while(currentBlock->q.empty()){
               if(currentBlock->next != NULL){
                   currentBlock = currentBlock->next;
               }
               else{
                   currentBlock = headBlock;
               }
               if(i == 5){
                   std::cout<<"something is fucked" <<std::endl;
               }
               i++;
        }
        int pos = currentBlock->q.front();
        std::cout << "Postion " << pos << std::endl;
        currentBlock->q.pop();
        int x = pos %10;
        pos/=10;
        int y = pos;
        rchar.first = (char)'0' + x;
        rchar.second = (char) 'A' + y;
        return rchar;
            
}
    
    std::pair<char, char> AI::seekAndDestroy(){
        std::cout<< "IS seek empty " << seek.empty() << std::endl; 
        if(!seek.empty()){
            lastChoice = seek.front();
            seek.pop();
        }
        else{
            //ship stopped progressing down this branch
            //go back to inital spot to check if there is another side
            lastChoice = initialHit;
            createQueue();
            //single recursive reset
//            lastChoice = seek.front();
//            seek.pop();
            if(reset){
                reset = false;
                sunk();
            }
            else{
                 reset = true;
            }
        }
        std::cout<< "Last Choice SEEK " << lastChoice.first << " " << lastChoice.second  << std::endl;
        return lastChoice;
    }
    bool AI::getFind(){
        return currentBlock->find;
    }
    void AI::lastChoiceHit(){
        // if first hit move back to block that was hit 
        std::cout << "Find? " << currentBlock->find << std::endl;
        if(!currentBlock->find){
            initialHit = lastChoice;
            if(currentBlock->prev!= NULL){
            currentBlock = currentBlock->prev;
            }
            //used to mark if seek mode
            currentBlock->find = true;
             std::cout << "Start Quene" << std::endl;
            createQueue();
        }
        else{
            lastSearch = true;
            //clear the current Queue for the next postion to check
            std::cout << "Clear Quene" << std::endl;
            clearQueue();
             std::cout << "start Quene" << std::endl;
            createQueue();
        }
    }
    
    void AI::createQueue() {
        std::cout <<"queue start" << std::endl;
    std::pair<char, char> temp = lastChoice;
    
    // Check left of hit
    if (temp.first != '0') {
        std::pair<char, char> leftTemp = temp;
        leftTemp.first = (char)(leftTemp.first - 1);
        seek.push(leftTemp);
    }

    // Check top
    temp = lastChoice;  // Reset to the original value before modifying
    if (temp.second != 'A') {
        std::pair<char, char> topTemp = temp;
        topTemp.second = (char)(topTemp.second - 1);
        seek.push(topTemp);
    }

    // Check right
    temp = lastChoice;  // Reset to the original value before modifying
    if (temp.first != '9') {
        std::pair<char, char> rightTemp = temp;
        rightTemp.first = (char)(rightTemp.first + 1);
        seek.push(rightTemp);
    }

    // Check bottom
    temp = lastChoice;  // Reset to the original value before modifying
    if (temp.second != 'J') {
        std::pair<char, char> bottomTemp = temp;
        bottomTemp.second = (char)(bottomTemp.second + 1);
        seek.push(bottomTemp);
        
    }
    std::cout <<"queue end" << std::endl;
}
    void AI::clearQueue(){
        while (!seek.empty()) {
             seek.pop();
        }
    }
    
    void AI::sunk(){
        clearQueue();
        currentBlock->find = false;
         if(currentBlock->next != NULL){
            currentBlock = currentBlock->next;
        }
        else{
            currentBlock = headBlock;
        }
        lastSearch = false;
    };
    