/* 
 * File:   dedGame.h
 * Author: Ded
 *
 * Created on March 21, 2018, 9:51 PM
 */

#include <string>
#ifndef DEDGAME_H
#define DEDGAME_H

#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;


/**
 * Does a log. weighted roll, such that A is n times more likely to succeed if 
 * A = 2^n * B (or vice versa).
 * @param a the 'instigator'
 * @param b the 'defender'
 * @returns true if A succeeds, false otherwise.
 */
bool succeedsRoll(float a, float b);

/**
 * Asks user to confirm/deny the message
 * @param message the message that will be displayed 
 * @return true if Y/y, false if N/n (loops otherwise)
 */
bool confirmMessage(string m);


/**
 * Gets the 'multiplier' involved, such that the difference between a and b
 * would have to double in size to increase the multiplier by 1.
 * @param a
 * @param b
 * @return 
 */
float getMult(float a, float b);


#endif /* DEDGAME_H */

