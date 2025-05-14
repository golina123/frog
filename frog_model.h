#pragma once
#include "subjects.h"
#include "position.h"
#include <vector>
#include <random>  
#include <algorithm>

enum Action {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        TREE,
	SWAMP,
        PLACE_EMPTY,
        RESET
    };


class model {
private:
    subjects world_objects;
    std::vector<position> trees;
    std::vector<position> swamp;
    std::vector<position> objects;
    coords player_pos_;

    int screen_width_ = 80;
    int screen_height_ = 24;

    void move_player(int dx, int dy);
    void plant_tree(int dx, int dy);
    void grow_swamp();
    void fight_swamp();
    
public:
    model();
    void process_action(Action action);
    void rebuild();
    void set_screen_size(int width, int height)
    {
        screen_width_ = width;
        screen_height_ = height;
    }
    
    int get_screen_width() const { return screen_width_; }
    int get_screen_height() const { return screen_height_; }    

    const std::vector<position>& get_trees() const;
    const std::vector<position>& get_swamp() const;
    const std::vector<position>& get_objects() const;
    coords get_player_pos() const;
};
