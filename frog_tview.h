//tview.h
#pragma once

#include "frog_view.h"
#include <cstdlib>

enum colors {red = 1, green = 2, yellow = 3, blue = 4, pink = 5, cyan = 6, white = 7};

class frog_tview : public frog_view{
	private:
		int screen_x, screen_y;
                void  clscr();
                void cursor(int x, int y);
                void get_color(enum colors c);

        public:
                frog_tview();
		void draw();
};
