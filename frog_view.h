//view.h
#pragma once

class frog_view

{
        private:
                int a;
        public:
		virtual void draw() = 0;
                static frog_view *getview(const char*x);
		
};
