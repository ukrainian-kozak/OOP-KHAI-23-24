#pragma once

#include "kitchen.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

namespace my {

    class studio : public room {
        private:
            kitchen kitchen_;
            int number_;
            char* name_;

        public:
            studio();
            studio(unsigned int, unsigned int, unsigned int, int, const char *);
            studio(const studio&);
            studio(studio&&) = delete;
            studio& operator=(const studio&);
            studio operator=(studio&&) = delete;

            void set_name(char *);
            void set_number(unsigned int);

            unsigned int get_kitchen_square();
            char *get_name();

            ~studio() override;

            friend std::ostream& operator<<(std::ostream&, const studio&);
            friend std::istream& operator>>(std::istream&, studio&);
    };

}
