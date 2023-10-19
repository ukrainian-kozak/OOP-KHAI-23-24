#pragma once

#include "room.h"


namespace my {

    class kitchen : public room {
        private:
            unsigned int square_;
        public:
            kitchen();
            kitchen(unsigned int width, unsigned int height, unsigned int length);
            
            unsigned int& get_square();
            unsigned int get_square() const;
            void set_square(unsigned int);
    };
}
