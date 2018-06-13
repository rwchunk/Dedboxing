/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Match.cpp
 * Author: Dedster
 * 
 * Created on May 20, 2018, 2:07 PM
 */

#include "Match.h"
#include "dedGame.h"

using namespace std;
Match::Match() {
    this->boxers = new Boxer[2];
    seconds = 0;
    roundTime = 999999;
    downLimit = 999;
    numRounds = 500;
}

Match::Match(const Match& orig) {
}

Match::~Match() {
}


void Match::selectBoxer(){
    string s;
    for(int i = 0; i < 2; i++)
    {
        while (true)
        {
            cout << "Enter the name of Boxer " << i + 1 << "." << endl;
            cin >> s;
            if(boxers[i].loadFromFile(s))
                break;
            if (confirmMessage(s + ".bxr not found. Create?"))
            {
                boxers[i].createNew(s);
                break;
            }
        }
    }
}

void Match::startMatch(int numRounds, int downCount, int roundTime)
{
    this->numRounds = numRounds;
    this->downLimit = downCount;
    this->roundTime = roundTime;
    startMatch();
}

void Match::startMatch(){
    float healthRecov = 15;
    float factor = .50;
    for(round = 1; round <= numRounds; round++)
    {
        cout<< "ROUND " << round << "!\nKAN\nFIGHT!\n";
        for(seconds = 0; seconds <= roundTime; seconds+=5)
        {
            printTime();
            throwPunch();

            for(int i = 0; i<2; i++)
            {
                if(boxers[i].isDown())
                {
                    if (boxers[i].down(&boxers[(i + 1) % 2], downLimit))
                        return;
                }
                boxers[i].decay(1);
            }
            printStats();
        }
        cout << "KAN!" << endl << "Recovers " << healthRecov << endl << endl;
        for(int i = 0; i<2; i++)
        {
            boxers[i].regen(healthRecov);
            boxers[i].interval();
        }
            healthRecov *= factor;
    }
}

void Match::printTime()
{
    int m = seconds / 60;
    int s = seconds % 60;
    cout << "*******************" << endl;
    cout << "Round: " << round << "/" << numRounds <<" " << m << ":"
            << ((s < 10)?"0":"") << s << endl;
}

void Match::throwPunch()
{
    if(boxers[0].outSpeeds(boxers[1]))
        boxers[0].throwPunch(&boxers[1]);
    else
        boxers[1].throwPunch(&boxers[0]);
}

void Match::printStats()
{
    for(int i = 0; i < 2; i++)
    {
        boxers[i].printStats();
        cout << endl;
    }
}