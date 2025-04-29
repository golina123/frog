//terminal.h
#pragma once

#include <termios.h>
#include <unistd.h>

class Terminal{
	private:
		struct termios oldt_;
	public:
		Terminal();
    		~Terminal();

    		void enable();
   		void restore();
};
