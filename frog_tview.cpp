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
}

frog_tview::~frog_tview() = default;

void frog_tview::clscr() //cleaning screen
{
	cout<<"\033[H\033[J";
        std::flush(std::cout);
}

void frog_tview::cursor(int x, int y) //move cursor in the point
{
	x = std::max(1, std::min(x, screen_x));
        y = std::max(1, std::min(y, screen_y));
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
    
    // draw player
    auto pos = m.get_player_pos();
    pos.first = std::max(1, std::min(pos.first, screen_x));
    pos.second = std::max(1, std::min(pos.second, screen_y));

    cursor(pos.first, pos.second);
    get_color(red);
    std::cout << "P";
    
    for(const auto& tree : m.get_trees()) {
        cursor(tree.get_pos().first, tree.get_pos().second);
        get_color(green);
        std::cout << "T";
    }

    for(const auto& s : m.get_swamp()) {
        cursor(s.get_pos().first, s.get_pos().second);
        get_color(blue);
        std::cout << "#";
    }

     for(const auto& obj : m.get_objects()) {
        cursor(obj.get_pos().first, obj.get_pos().second);
        get_color(yellow);
        std::cout << "U";
    }
    std::cout.flush();

}
