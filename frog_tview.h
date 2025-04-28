//tview.h
#pragma once

#include "frog_view.h"
#include "frog_model.h"
#include <cstdlib>
#include <termios.h>

enum colors {red = 1, green = 2, yellow = 3, blue = 4, pink = 5, cyan = 6, white = 7};

class frog_tview : public frog_view{
	private:
		int screen_x, screen_y;
                void clscr();
                void cursor(int x, int y);
                void get_color(enum colors c);
		void restore_terminal();
		void setup_terminal();
		struct termios oldt_;
          
        public:
                frog_tview();
		~frog_tview() override;
		void draw(const model& m) override;
};
