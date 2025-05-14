//model.cpp
#include "frog_model.h"


model::model() : player_pos_({0, 0})
{
    objects = world_objects.get_a();
    if (!objects.empty()) {
        player_pos_ = objects[0].get_pos();
    }
}

void model::process_action(Action action) 
{
    switch(action) {
        case MOVE_UP:    
		{
			move_player(0, -1);
			grow_swamp();
		       	break;
		}
        case MOVE_DOWN: 
		{	
			move_player(0, 1);  
			grow_swamp();
			break;
		}
        case MOVE_LEFT:  
		{
			move_player(-1, 0); 
			grow_swamp();
			break;
		}
        case MOVE_RIGHT: 
		{
			move_player(1, 0); 
		        grow_swamp();
			break;
		}
	case TREE: 
			 {
				 move_player(1, 1); 
				 plant_tree(-1, -1);
				 fight_swamp();
				 break;
			 }
	default: break;
    }
}

void model::rebuild() 
{
     objects.clear();
     trees.clear();
     swamp.clear();
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


void model::grow_swamp()
{
	  
	 coords swamp_center = {screen_width_/2, screen_height_/2};

	 const int max_growth_distance = (screen_width_ < screen_height_) ? screen_width_ : screen_height_;

	 if (swamp.empty()) 
	 {
        	swamp.emplace_back(swamp_center, objects::swamp);
        	return;
    	 }

	 if (swamp.size() >= max_growth_distance * max_growth_distance*3) 
		 return;

	std::vector<position> new_swamp_tiles;
	std::random_device rd; 
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

    for (const auto& swamp_tile : swamp) 
    {
	    int neighbor_count = 0;
	    coords pos = swamp_tile.get_pos();

	    for(int x = -1; x <= 1; x++)
	    {
		    for(int y = -1; y<=1; y++)
		    {
			    if(x == 0 && y == 0) continue;

			    coords check_pos = {pos.first + x, pos.second + y};
			       
			    bool is_swamp = std::any_of(swamp.begin(), swamp.end(), [&check_pos](const position& p) 
			    {
                        	return p.get_pos() == check_pos;
                            });

			    if(is_swamp) 
			    {
			    	neighbor_count ++;
			    }
		    }
	    }

	    if (neighbor_count >= 7) continue;

	    for (int x = -1; x <= 1; x++) 
	     {
            		for (int y = -1; y <= 1; y++) 
			{
                		if (x == 0 && y == 0) continue;

				coords new_pos = {pos.first + x, pos.second + y};

				if (new_pos.first < 1 || new_pos.first > screen_width_ || new_pos.second < 1 || new_pos.second > screen_height_) 
				{
                   			 continue;
                 		}

				bool exists = std::any_of(swamp.begin(), swamp.end(), [&new_pos](const position& p) { return p.get_pos() == new_pos; });

                		bool is_tree = std::any_of(trees.begin(), trees.end(),[&new_pos](const position& p) { return p.get_pos() == new_pos; });

                	       if (!exists && !is_tree && dis(gen) < 0.3)
	       			{
                    			new_swamp_tiles.emplace_back(new_pos, objects::swamp);
			
				}	
	                }
    	     }	

	}
     swamp.insert(swamp.end(), new_swamp_tiles.begin(), new_swamp_tiles.end());
}


void model::fight_swamp()                //rules of neiborhood tree and swamp
{
        for(auto it = swamp.begin(); it != swamp.end();)
	{
		bool near_tree = false;

		for(auto& tree: trees)
		{
			int t1 = abs(tree.get_pos().first - it->get_pos().first);
			 int t2 = abs(tree.get_pos().second - it->get_pos().second);
			 if(t1 <= 1 && t2 <= 1)
			 {
				 near_tree = true;
				 break;
			 }
		}

		if(near_tree == true)          //find tree-> remove swam cell
			it = swamp.erase(it);
		else
			++it;


	}
}
const std::vector<position>& model::get_objects() const {
    return objects;
}

const std::vector<position>& model::get_trees() const {
    return trees; 
}
const std::vector<position>& model::get_swamp() const {
    return swamp;
}
coords model::get_player_pos() const {
    return player_pos_;
}

