#include "kitchen.h"

namespace my {

    kitchen::kitchen() : room(), square_(0) {}

    kitchen::kitchen(unsigned int width, unsigned int height, unsigned int length)
        : room(width, height, length), square_(width_ * length_) {}

    unsigned int& kitchen::get_square() {
        return square_;
    }

    unsigned int kitchen::get_square() const {
        return square_;
    }

    void kitchen::set_square(unsigned int square) {
        square_ = square;
    }
}
