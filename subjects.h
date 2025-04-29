//subjects h
#pragma once
#include "position.h"
#include <vector>

class subjects{
	private:
                coords h;
                std::vector<position> a;
        public:
                subjects();
                const std::vector<position>& get_a() const
                { return a;}
};
