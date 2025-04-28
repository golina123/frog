//view.h
#pragma once
#include "frog_model.h"

class frog_view

{
        private:
                int a;
        public:
		virtual ~frog_view() = default;
		virtual void draw(const model& m) = 0;
                static frog_view *getview(const char*x);
		
};
