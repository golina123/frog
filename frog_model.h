#pragma once
#include "subjects.h"
#include "position.h"
#include <vector>

class model {
private:
    subjects world_objects;
    std::vector<position> objects;
    
public:
    model();
    void update();
    const std::vector<position>& get_objects() const;
};
