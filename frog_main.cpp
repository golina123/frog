//main.cpp 
#include <stdio.h>
#include <iostream>
#include "frog_view.h"
#include "frog_model.h"
#include "frog_terminal.h"
#include <termios.h>
#include <unistd.h>
#include "sfml_render.h"
#include <string>

using namespace std;

int main(int ac, const char *av[])
{
	model game_model;
       // frog_view *view = frog_view::getview(ac > 1 ? av[1] : ""); //draw
	Terminal terminal;
    	terminal.enable();

	bool graphics_mode = (ac > 1 && string(av[1]) == "-g");

 	   if (graphics_mode) {
        				// Графический режим (SFML)
        	SFMLRenderer renderer(game_model);
        	renderer.run(); // Запускаем SFML-цикл
    	   }
	   else {
        				// Терминальный режим
        	frog_view* view = frog_view::getview(ac > 1 ? av[1] : "");
		cout<< "Game start \n";

		while(true)
       		{
                	                   // Обработка ввода
       	 		char c;
        		if(read(0, &c, 1) == 1)
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
        	usleep(200000); // Задержка
    		}
	      }
	exit_loop:
              
    	cout<< " hello i'm frog from main \n";
    	return 0;
}
	

