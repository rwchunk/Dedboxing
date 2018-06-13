/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Boxer.cpp
 * Author: Dedster
 * 
 * Created on April 1, 2018, 4:59 PM
 */

#include "Boxer.h"
#include "dedGame.h"
#include "Punch.h"
#include <fstream>
#include <string.h>
#include <cstring>
#include <math.h>
#include <complex>

Boxer::Boxer() {
    hp = 100;
    stamina = 100;
    maxStamina = 100;
    downs = 0;
    curDecay = 1;
    totalDowns = 0;
    punchTaken = punchTakenTotal = 0;
}



Boxer::~Boxer() {
}

void Boxer::setStats(float str, float frt, float tch, float def, float speed,
        string name)
{
    mStr = strength = str;
    mFort = fort = frt;
    mTech = tech = tch;
    mDef = this->def = def;
    mSpd = this->speed = speed;
    this->name = name;
}

void Boxer::saveToFile()
{
    string fileName = name + ".bxr";
    ofstream outFile((fileName).c_str(), ios::binary);
    outFile.write((char*) &strength, sizeof(float));
    outFile.write((char*) &fort, sizeof(float));
    outFile.write((char*) &tech, sizeof(float));
    outFile.write((char*) &def, sizeof(float));
    outFile.write((char*) &speed, sizeof(float));
    outFile.write((char*) &numPunches, sizeof(int));
    for(int i = 0; i < numPunches; i++)
        outFile.write((char*) &punchList[i], sizeof(Punch));
}

bool Boxer::loadFromFile(string name)
{
    float st, ft, tc, df, sp;
    int n;
    string fileName = name + ".bxr";
    ifstream boxerFile;
    boxerFile.open(fileName.c_str(), ios::binary);
    if(!boxerFile.is_open())
            return false;
        boxerFile.read((char*) &st, sizeof(float));
        boxerFile.read((char*) &ft, sizeof(float));
        boxerFile.read((char*) &tc, sizeof(float));
        boxerFile.read((char*) &df, sizeof(float));
        boxerFile.read((char*) &sp, sizeof(float));
        boxerFile.read((char*) &n, sizeof(int));
        cout << name + " found with following stats:" << endl
                << "Strength: " << st << endl
                << "Fortitude: " << ft << endl
                << "Technique: " << tc << endl
                << "Defense: " << df << endl
                << "Speed: " << sp << endl
                << "Number of Punches: " << n << endl;
        if(confirmMessage("Load boxer?: "))
        {
            
//            punchList = new Punch[n];
//            for (int i = 0; i < n; i++)
//            {
//                boxerFile.read((char*) &punchList[i], sizeof(Punch));
//            }
            
            punchList = new Punch[4];
            punchList[0] = Punch(.9, 1, 1, "Jab");
            punchList[1] = Punch(.75, 3, 2, "Straight");
            punchList[2] = Punch(.5, 5, 6, "Upper");
            punchList[3] = Punch (.7, 4, 4, "Hook");
            setStats(st,ft,tc,df,sp, name);
            numPunches = 4;
            boxerFile.close();
            return true;
        }
        boxerFile.close();
        return false;
}

void Boxer::createNew(string name)
{
    this->name = name;
    cout << "Strength?" << endl;
    cin >> strength;
    cout << "Fortitude?" << endl;
    cin >> fort;
    cout << "Technique?" << endl;
    cin >> tech;
    cout << "Defense?" << endl;
    cin >> def;
    cout << "Speed?" << endl;
    cin >> speed;
    mStr = strength;
    mFort = fort;
    mTech = tech;
    mDef = this->def;
    mSpd = this->speed;
    /**
     * 
     
    cout  << "How many punches?" << endl;
    cin << n;
     **/
    numPunches = 3;
    punchList = new Punch[numPunches];
    punchList[0] = Punch(.9, 1, 1, "Jab");
    punchList[1] = Punch(.75, 3, 2, "Straight");
    punchList[2] = Punch(.5, 5, 3, "Upper");
    this->saveToFile();
            /**
     * for(int i = 0; i < n; i++)
    {
        punchList[i] = Boxer();
    }
    **/
        
}

void Boxer::throwPunch(Boxer* o) {
    int pN = rand() % numPunches;
    Punch p = punchList[pN];
    if (p.getCost() >= stamina)
    {
        cout << name << " takes a moment to breath" << endl;
        stamina +=1;
        o->throwPunch(this);
        return;
    }
    cout << name << " throws a " << p.getName() << " at " << o->getName() 
            << endl;
    if(!succeedsRoll(speed, o->speed))
    {
        cout << o->name << " dodges it." << endl;
        return;
    }
    
    int damage = p.getPower() * getMult(strength, o->fort);
//   decay(p.getCost());
    damage *= 1.5;
    float mult = (rand() % 1500 / 1000.0) + .5;
    damage *= mult;
    damage = max(damage, 1);

    if(!hits(*o))
    {
        cout << o->name << " blocks it and takes " << damage / 2 << " damage." 
                <<endl;
        o->stamina -= damage / 2;
        return;
    }
    cout << o->name << " takes " << damage << " damage. ( x" << mult << " )" << endl;
    o->takesDamage(damage);
}

bool Boxer::outSpeeds(Boxer o)
{
    return succeedsRoll(speed, o.speed);
}


bool Boxer::hits(Boxer o)
{
    return succeedsRoll(tech, o.def);
}

void Boxer::printStats()
{
    int i = 0;
    string s = "";
    
    //This is for standard 3 kd rules, but since I made them customizable
//    for (i = 0; i < 3 && i < downs; i++)
//    {
//        s.append("X");
//    }
//    for(i; i < 3; i++)
//        s.append("O");
    
    cout << "Downs: " << downs << "(" << totalDowns << ") | " << name
            << ": " << (int)stamina << " / "<< (int)hp << endl << "Strength: "
            << strength << " Defense: "<< fort << " Hit:" << tech 
            << " Block: " << def << " Speed: "
            << speed << " " << curDecay <<endl;
}

void Boxer::takesDamage(int d)
{
    hp = max(0, hp - d);
    punchTakenTotal++;
    stamina -= 2 * d;
}

void Boxer::decay(double d)
{
    float ratio =  pow(0.997127, 100-stamina);
    curDecay = ratio;
    strength = max(1, (int) (mStr * ratio));
    fort = max(1, (int) (mFort * ratio));
    tech = max(1, (int) (mTech * ratio));
    def = max(1, (int) (mDef * ratio));
    speed = max(1, (int) (mSpd * ratio));
}
bool Boxer::isDown()
{
    return stamina <= 0;
}

bool Boxer::down(Boxer* o, int downLimit)
{
    downs++;
    totalDowns++;
    cout << name << " DOWN!" << endl;
    int i;
    int curHealed = 0;
    int target = max(3, 7 - hp / 10) + stamina / -5;
    if (hp <= 1)
        target = 999999;
    if (downs >= downLimit)
    {
        cout << "TKO" << endl;
        return true;
    }
    for (i = 0; i < 10 && curHealed < target; i++)
    {
        curHealed++;
        cout << i + 1 << "! ";
    }
    cout << endl;
    if (i == 10)
    {
        cout << "KAN KAN KAN!" << endl;
        return true;
    }
    stamina = 0;
    stamina = hp;
    o->recoverHalf();
    return false;
}

void Boxer::regen()
{
    stamina = min(hp * 1.0, stamina + 5.0);
}

void Boxer::regen(float x)
{
    cout << name << "recovers " << x<< " HP" << endl;
    hp = min(100.0, hp * 1.0 + x);
}

void Boxer::recoverHalf()
{
   // hp= min(100, hp + 5);
    int missing = hp - stamina;
    stamina += missing / 2;
    punchTaken /= 1.5;
}

void Boxer::interval()
{
   // hp = min(100, hp + (hp) / 10);
    //stamina = hp;
    recoverHalf();
    downs = 0;
}