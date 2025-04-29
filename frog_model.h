#pragma once
#include "subjects.h"
#include "position.h"
#include <vector>

enum Action {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        TREE,
        PLACE_EMPTY,
        RESET
    };
class model {
private:
    subjects world_objects;
    std::vector<position> trees;
    std::vector<position> objects;
    coords player_pos_;
    void move_player(int dx, int dy);
    void plant_tree(int dx, int dy);
    
public:
    model();
    void process_action(Action action);
    void rebuild();
    const std::vector<position>& get_trees() const;
    const std::vector<position>& get_objects() const;
    coords get_player_pos() const;
};
