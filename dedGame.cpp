
/* 
 * File:   dedGame.cpp
 * Author: Dedster
 * 
 * Created on March 21, 2018, 9:51 PM
 */

#include <string.h>
#include <complex>
#include "dedGame.h"



using namespace std;

bool succeedsRoll(float a, float b)
{
    if (a >= b)
        {
            float ratio =  a / b;
            float x = log2(ratio) + 2;
            float winCond = 1 / x;
            int roll = rand() % 100;
            int winCondI = floor(winCond * 100);
            return ((roll) > winCondI);
        }
            float ratio = b / a;
            float x = log2(ratio) + 2;
            float loseCond = 1 / x;
            int loseCondI = floor(loseCond * 100);
            int roll = (rand() % 100);
            return (roll <= loseCondI);
}

float getMult(float a, float b)
{
    float x;
    float ratio = a / b;
    x = log2(ratio);
    if (x == 0)
        return 1;
    else if(x < 0)
    {
        x *= -1;
        return pow(x + 1, -1);
    }
    return x + 1;
}

bool confirmMessage(string m)
{
    char inp;
    while (true)
        {
            cout << m;
            cin >> inp;
            if (inp == 'N' || inp == 'n')
                return false;
            if (inp == 'Y' || inp == 'y')
            {
                return true;
            }
        }   
    return true;
}
