//tview.cpp
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include <unistd.h>
#include "frog_tview.h"

using namespace std;

frog_tview::frog_tview() //screen size
{
        struct winsize c;
        ioctl(1, TIOCGWINSZ, &c);
        screen_y = c.ws_row;
        screen_x = c.ws_col;

}

void frog_tview::clscr() //cleaning screen
{
	cout<<"\033[H\033[J";
        std::flush(std::cout);
}

void frog_tview::cursor(int x, int y) //move cursor in the point
{
	cout << "\033[" << y << ";" << x << "H";
        std::flush(std::cout);
}


void frog_tview::get_color(enum colors c) //change color
{

	cout<<"\033[3"<<c<<"m";
        std::flush(std::cout);
}
void frog_tview::draw()
{
	clscr();
	cursor(screen_x/2, screen_y/2);
	cout<<"bye ";

}
