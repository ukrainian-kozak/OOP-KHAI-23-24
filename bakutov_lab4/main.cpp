#include <iostream>
#include "agency.h"


int main() {

    const char* name = nullptr;
    for ( ;; ) {
        std::cout << "1) Add human to the table.\n";
        std::cout << "2) Delete human from table.\n";
        std::cout << "3) My variant task.\n";
        std::cout << "4) Print table.\n";
        std::cout << "5) Exit.\n";
        std::cout << "After input 'character', just press ENTER. Even after incorrect input, press ENTER and then try again to enter the right character.\n";

        int c = my::get_num(1, 5);
        switch (c) {
            case 1:
                my::add_human("database.dat");
                break;
            case 2:
                name = my::get_name();
                my::erase_human("database.dat", name);
                break;
            case 3:
                my::find("database.dat", my::get_num());
                break;
            case 4:
                my::print_agency("database.dat");
                break;
            case 5:
                exit(0);
                break;
            default:
                break;
        }
    }
    return 0;
}
