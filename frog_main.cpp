//main.cpp  ttttttttt
#include <stdio.h>
#include <iostream>
#include "frog_view.h"
using namespace std;

int main(int ac, const char *av[])
{
        frog_view *v = frog_view::getview(av[1]); //draw
	v->draw();
	std::cout<< " hello i'm frog from main \n";
	return 0;
}

