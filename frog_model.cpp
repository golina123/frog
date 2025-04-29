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
				 plant_tree(-1, -1);
				 break;
			 }
	default: break;
    }
}

void model::rebuild() 
{
     objects.clear();
     trees.clear();
                                       // Пересоздаем начальное состояние
    objects = world_objects.get_a();
    
                                        // Сбрасываем позицию игрока
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

void model::plant_tree(int dx, int dy)
{
	coords new_pos = {player_pos_.first + dx,  player_pos_.second + dy};
	trees.emplace_back(new_pos, objects::tree);

}
const std::vector<position>& model::get_objects() const {
    return objects;
}

const std::vector<position>& model::get_trees() const {
    return trees; 
}
coords model::get_player_pos() const {
    return player_pos_;
}
