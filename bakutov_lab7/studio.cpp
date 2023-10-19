#include "studio.h"

namespace my {

    studio::studio() : room(), kitchen_(), number_(0), name_(nullptr) { 
        name_ = new char[255];
    }


    studio::studio(unsigned int width, unsigned int height, unsigned int length, int number, const char *name)
        : room(width, height, length), kitchen_(width / 2, height, length / 2), 
        number_(number), name_(nullptr) {
            name_ = strdup(name);
        }

    studio::studio(const studio& other) {
        if (this != &other) {
            delete [] name_;

            width_ = other.width_;
            height_ = other.height_;
            length_ = other.length_;
            kitchen_.set_width(width_ / 2);
            kitchen_.set_height(height_);
            kitchen_.set_length(length_ / 2);
            kitchen_.set_square(length_ * width_);
            number_ = other.number_;
            
            name_ = new char[strlen(other.name_ + 1)];
            strcpy(name_, other.name_);
            name_[strlen(other.name_)] = '\0';
        }
    }

    studio& studio::operator=(const studio& other) {
        if (this != &other) {
            delete [] name_;

            width_ = other.width_;
            height_ = other.height_;
            length_ = other.length_;
            kitchen_.set_width(width_ / 2);
            kitchen_.set_height(height_);
            kitchen_.set_length(length_ / 2);
            kitchen_.set_square(length_ * width_);
            number_ = other.number_;
            name_ = other.name_;

            name_ = new char[strlen(other.name_ + 1)];
            strcpy(name_, other.name_);
            name_[strlen(other.name_)] = '\0';
        }

            return *this;
    }

    void studio::set_name(char* name) {
        if (name_)
            delete [] name_;
        name_ = name;
        name = nullptr;
    }

    void studio::set_number(unsigned int num) {
        number_ = num;
    }

    unsigned int studio::get_kitchen_square() {
        return kitchen_.get_square();
    }

    char *studio::get_name() {
        return name_;
    }

    studio::~studio() {
        delete [] name_;
    }

    std::ostream& operator<<(std::ostream& os, const studio& st) {
        os << st.width_ << ' ' << st.height_ << ' ' << st.length_ 
            << ' ' << (st.width_ / 2)
            << ' ' << st.height_
            << ' ' << (st.length_ / 2)
            << ' ' << st.width_ * st.length_ 
            << ' ' << st.number_ << ' ' << st.name_;

        return os;
    }

    std::istream& operator>>(std::istream& in, studio& st) {
        in >> st.width_ >> st.height_ >> st.length_ 
            >> st.kitchen_.get_width() >> st.kitchen_.get_height()
            >> st.kitchen_.get_length() >> st.kitchen_.get_square()
            >> st.number_;

        char tempName[256];
        in >> tempName;

        st.name_ = new char[strlen(tempName) + 1];
        strcpy(st.name_, tempName);

        return in;
    }
}
