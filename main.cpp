#include "mainWindow.h"
#include "Boxer.h"
#include "dedGame.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <valarray>
#include <fstream>
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	mainWindow w;
	w.show();
	return a.exec();
}
