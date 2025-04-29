//frog_terminal.cpp

#include "frog_terminal.h"
using namespace std;

Terminal::Terminal()
{
    tcgetattr(1, &oldt_);
}
Terminal::~Terminal()
{
	restore();
}
void Terminal::enable()
{
	 struct termios newt = oldt_;
    	newt.c_lflag &= ~(ICANON | ECHO);
    	tcsetattr(1, TCSANOW, &newt);
}
void Terminal::restore() {
    tcsetattr(1, TCSANOW, &oldt_);
}
