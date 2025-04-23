//model.cpp
#include "frog_model.h"

model::model()
{
    objects = world_objects.get_a();
}

void model::update() 
{
     std::vector<position> tmp;

}

const std::vector<position>& model::get_objects() const {
    return objects;
}
