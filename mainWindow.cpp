#include "mainWindow.h"
#include "Match.h"

mainWindow::mainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	srand(time(NULL));
	Match m;
	m.selectBoxer();
	m.startMatch(12, 3, 180);
}
