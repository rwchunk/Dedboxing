/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Match.h
 * Author: Dedster
 *
 * Created on May 20, 2018, 2:07 PM
 */

#ifndef MATCH_H
#define MATCH_H
#include "Boxer.h"
#include "dedGame.h"
#include <stdio.h>
#include <string>

class Match {
public:
    Match();
    Match(const Match& orig);
    virtual ~Match();
    /**
     Picks the two boxers to fight
     */
    void selectBoxer();
    
    /**
     Pits the two selected boxers against each other
     @param numRounds how many rounds
     @param downCount Number of downs until TKO
     @param roundTime How long each round will last, in seconds 
     */
    void startMatch(int numRounds, int downCount, int roundTime);
    void startMatch();
    
private:
    int round;
    int seconds;
    int roundTime, downLimit, numRounds;
    Boxer* boxers;
    void printTime();
    void printStats();
    
    
    void throwPunch();
};

#endif /* MATCH_H */

