/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Block.h
 * Author: aawri
 *
 * Created on October 29, 2023, 2:37 PM
 */

#ifndef BLOCK_H
#define BLOCK_H
#include <queue>
struct Block{
    bool find;
    std::queue<int> q;
    Block * next;
    Block * prev;
 };


#endif /* BLOCK_H */

