//tview.cpp
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include <unistd.h>
#include "frog_tview.h"
#include <termios.h>

using namespace std;

//constructor+ destructor
frog_tview::frog_tview() //screen size
{
        struct winsize c;
        ioctl(1, TIOCGWINSZ, &c);
        screen_y = c.ws_row;
        screen_x = c.ws_col;
	setup_terminal();

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

void frog_tview::draw(const model& m) {
    clscr();
    
    // Отрисовка игрока
    auto pos = m.get_player_pos();
    cursor(pos.first, pos.second);
    get_color(red);
    std::cout << "P";
    std::cout.flush();

     for(const auto& obj : m.get_objects()) {
        cursor(obj.get_pos().first, obj.get_pos().second);
        get_color(green);
        std::cout << "T";
    }
}
// Реализация setup_terminal()
void frog_tview::setup_terminal() {
    tcgetattr(1, &oldt_);
    struct termios newt = oldt_;
    newt = oldt_;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(1, TCSANOW, &newt);
}

// Реализация restore_terminal()
void frog_tview::restore_terminal() {
    tcsetattr(1, TCSANOW, &oldt_);
}

// Реализация деструктора
frog_tview::~frog_tview() {
    restore_terminal();
}
