//model.cpp
#include "frog_model.h"

model::model() : player_pos_({0, 0})
{
    objects = world_objects.get_a();
    if (!objects.empty()) {
        player_pos_ = objects[0].get_pos();
    }
}

void model::process_action(Action action) {
    switch(action) {
        case MOVE_UP:    move_player(0, -1); break;
        case MOVE_DOWN:  move_player(0, 1);  break;
        case MOVE_LEFT:  move_player(-1, 0); break;
        case MOVE_RIGHT: move_player(1, 0);  break;
	case TREE: 
			 {
				 move_player(1, 1); 
				 break;
			 }
	default: break;
    }
}

void model::rebuild() 
{
     objects.clear();
    
    // 2. Пересоздаем начальное состояние
    objects = world_objects.get_a();
    
    // 3. Сбрасываем позицию игрока
    if (!objects.empty()) {
        player_pos_ = objects[0].get_pos();
    } else {
        player_pos_ = {0, 0};
    }

}

void model::move_player(int dx, int dy)
{
	player_pos_.first += dx;
	player_pos_.second += dy;
   
}

const std::vector<position>& model::get_objects() const {
    return objects;
}
coords model::get_player_pos() const {
    return player_pos_;
}
