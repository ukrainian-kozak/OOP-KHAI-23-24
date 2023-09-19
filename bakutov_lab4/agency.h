#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <cstring>
#include <limits>

namespace my {
    
    struct human {
        char* name_;
        char gender_;
        unsigned int height_;
        unsigned int age_;
        char* character_;
        char* skin_;
        unsigned int salary_;
        unsigned int n_div_;
        
        human(): name_(nullptr), gender_('\0'), height_(0),
                age_(0), character_(nullptr), skin_(nullptr),
                salary_(0), n_div_(0) {}

        human(const my::human&);
        human& operator=(const my::human&);
        ~human();

        friend std::istream& operator>>(std::istream& is, my::human& h);
        friend std::ostream& operator<<(std::ostream& os, const my::human& h);
    };
    
    
    unsigned int get_num(int a = -std::numeric_limits<int>::max(),
                int b = std::numeric_limits<int>::max());
    char* get_name();
    my::human create_human();
    void add_human(const char* file);
    void erase_human(const char* file, const char* name);
    void print_agency(const char* file);
    void find(const char* file, int val);
}


