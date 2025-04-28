//main.cpp 
#include <stdio.h>
#include <iostream>
#include "frog_view.h"
#include "frog_model.h"
#include <termios.h>
#include <unistd.h>
using namespace std;

int main(int ac, const char *av[])
{
	model game_model;
        frog_view *view = frog_view::getview(av[1]); //draw
	struct termios oldt, newt;
    	tcgetattr(1, &oldt);
   	newt = oldt;
    	newt.c_lflag &= ~(ICANON | ECHO);
    	tcsetattr(1, TCSANOW, &newt);
	
	while(true)
       	{
                                   // Обработка ввода
       	 	char c;
        	if(read(1, &c, 1) == 1)
	       	{
            		switch(c) {
                	case 'w': game_model.process_action(MOVE_UP); break;
                	case 's': game_model.process_action(MOVE_DOWN); break;
               	 	case 'a': game_model.process_action(MOVE_LEFT); break;
                	case 'd': game_model.process_action(MOVE_RIGHT); break;
			case 't': game_model.process_action(TREE); break;
                	case 'r': game_model.rebuild(); break; 
                	case 'q': goto exit_loop; 
            		}
                }

                                 // Отрисовка
        view->draw(game_model); // Передаем модель для отрисовки
        usleep(100000); // Задержка
    	}

	exit_loop:
                                       // Восстановление и очистка
   	tcsetattr(1, TCSANOW, &oldt);
    	delete view;
    	cout<< " hello i'm frog from main \n";
    	return 0;
}
	

