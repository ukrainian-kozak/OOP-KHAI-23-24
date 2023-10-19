#include "room.h"

namespace my {

    room::room() : width_(0), height_(0), length_(0) {}

    room::room(unsigned int width, unsigned int height, unsigned int length)
        : width_(width), height_(height), length_(length) {}

    void room::set_width(unsigned int width) {
        width_ = width;
    }

    void room::set_height(unsigned int height) {
        height_ = height;
    }

    void room::set_length(unsigned int length) {
        length_ = length;
    }

    unsigned int& room::get_width() {
        return width_;
    }

    unsigned int& room::get_height() {
        return height_;
    }

    unsigned int& room::get_length() {
        return length_;
    }

    unsigned int room::get_width() const {
        return width_;
    }

    unsigned int room::get_height() const {
        return height_;
    }

    unsigned int room::get_length() const {
        return length_;
    }
}
