//view.cpp
#include <iostream>
#include "frog_view.h"
#include "frog_tview.h"

frog_view *    frog_view::getview     (const char*x)
{
	std::cout<<"getview \n";
        return new frog_tview;

}
