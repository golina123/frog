//position,h
#pragma once

#include <utility>
#include <iostream>
#include <string>
#include <vector>

using coords = std::pair<int, int>;

enum objects {

        tree,
	water,
        empty, 
	swamp
};

class position{
        private:
                coords coord_;
                objects object_;
        public:

                position();
                position(coords c, objects o): coord_(c), object_(o) {}
                coords get_pos() const { return coord_; };
                objects get_def() const { return object_; };
};
