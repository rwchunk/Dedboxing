//============================================================================
// Name        : Boxing.cpp
// Author      : Dedster
// Version     : 0.5 maybe
// Copyright   : No copyright law in the universe will stop me!
// Description : boxan
//============================================================================


/*
 * TO DO:
 * Balance someday
 * Make punches be selected before initial speed decision is made (makes it so 
 *  stronger punches are less likely to even be thrown as opposed to more likely
 *  to miss.
 * Clean code
 *  Like, why the fuck does decay still take in a double
 *  While I'm at it should fix int/double/float shenanigans
 * Make punches character specific (maybe)
 * Make damage customization more user friendly. Or code friendly
 * 
 * 
 * 
 * 
 * add graphics
 */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <valarray>
#include <fstream>
#include "Boxer.h"
#include "dedGame.h"
#include "Match.h"

using namespace std;








int main() {
    srand(time(NULL));
    cout << "A fight is about to begin" << endl;
    Match m;
    m.selectBoxer();
    m.startMatch(12, 3, 180);
    return 0;
}
