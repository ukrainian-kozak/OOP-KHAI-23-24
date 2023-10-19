#pragma once 


namespace my {
    class room {
        protected:
            unsigned int width_;
            unsigned int height_;
            unsigned int length_;

        public:
            room();
            room(unsigned int width, unsigned int height, unsigned int length);

            void set_width(unsigned int width);
            void set_height(unsigned int height);
            void set_length(unsigned int length);

            unsigned int& get_width();
            unsigned int& get_height();
            unsigned int& get_length();

            unsigned int get_width() const;
            unsigned int get_height() const;
            unsigned int get_length() const;

            virtual ~room() {}
    };
}
