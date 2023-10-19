#include "studio.h"
#include <iostream>
#include <limits>
#include <regex>

namespace {

    void cin_handle() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void skip_spaces(char* name) {
        int j = 0;

        for (int i = 0; name[i] != '\0'; ++i)
            if (name[i] != '\t' && name[i] != ' ')
                name[j++] = name[i];

        name[j] = '\0';
    }

    unsigned int get_num() {

        int n;
        while (!(std::cin >> n)) {
            cin_handle();
            std::cout << "Wrong input\n";
        }
        return (n < 0) ? n *= -1 : n;
    }

    char* get_name() {
        char* name = nullptr;
        size_t lim = 100;

        std::regex pattern("^[a-zA-Z\\- ]+$", std::regex_constants::icase);

        for (;;) {
            if (name != nullptr) {
                delete [] name; 
                name = nullptr;
            }

            name = new char[lim];

            cin_handle();
            std::cout << "Input a name:\n";
            ssize_t len = getline(&name, &lim, stdin);

            if (len == -1) {
                std::cerr << "Error reading input. Please try again.\n";
                continue;
            }

            if (len > 0 && name[len - 1] == '\n') {
                name[len - 1] = '\0';
            } else if (len == 0) {
                std::cout << "Empty input. Please enter a valid name.\n";
                continue;
            }

            if (std::regex_match(name, pattern)) {
                skip_spaces(name);
                break;
            }
            std::cout << "Name can have only alphabet's characters, dash, and blanks.\n";
        }

        return name;
    }

    void print_file(std::fstream& file) {
        const int maxLines = 100;
        const int maxLineLength = 256; 
        char* lines[maxLines];
        int lineCount = 0;

        while (lineCount < maxLines && !file.eof()) {
            char line[maxLineLength];
            file.getline(line, maxLineLength);

            if (file.gcount() > 0) {
                lines[lineCount] = new char[file.gcount() + 1];
                std::strcpy(lines[lineCount], line);
                lineCount++;
            }
        }

        for (int i = 0; i < lineCount; i++) {
            std::cout << lines[i] << '\n';
            delete[] lines[i];
        }
    }

    void write_file(std::fstream& file) {
        my::studio st;

        std::cout << "Enter number of flat, please: ";
        unsigned int num = get_num();
        char* name = get_name();

        st.set_name(name);
        st.set_number(num);

        std::cout << "\nEnter width, height and length of room: ";
        st.get_width() = get_num();
        st.get_height() = get_num();
        st.get_length() = get_num();

        std::cout << std::endl;

        file << st << '\n';
        
    }
}

int main() {
    std::fstream file("lab7.txt", std::ios::in | std::ios::out | std::ios::app);

    for ( ;; ) {

        std::cout << std::endl;
        std::cout << "Enter '1' to read the file.\n";
        std::cout << "Enter '2' to write up to the file.\n";
        std::cout << "Enter '3' to exit.\n";
        
        int i;
        std::cin >> i;

        if (i == 1)
            print_file(file);
        else if (i == 2)
            write_file(file);
        else if (i == 3)
            break;

        file.clear();
        file.seekg(0, std::ios::beg);
    }

    file.close();
    return 0;
}
