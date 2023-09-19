#include "agency.h"
#include <cstring>

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

    
    char* get_character() {
        char* line = nullptr;
        size_t lim = 100;

        std::regex pattern("^(gentle|nasty|solid|tender|harmful|good|affectionate)$");

        for (;;) {
            if (line != nullptr) {
                delete[] line;
                line = nullptr;
            }

            line = new char[lim];

            cin_handle();
            std::cout << "Input character:\n";
            size_t len = getline(&line, &lim, stdin);

            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }

            if (std::regex_match(line, pattern)) {
                break;
            }

            std::cout << "gentle, nasty are bad\nsolid, tender, harmful are okay\ngood, affectionate are good\n(Usage: only lowercase characters!)\n";
        }

        return line;
    }

    char* get_skin() {
        char* skin = nullptr;
        size_t lim = 100;

        std::regex pattern("^(white|black|colors)$");

        for (;;) {
            if (skin != nullptr) {
                delete[] skin; 
                skin = nullptr;
            }

            skin = new char[lim];
            
            cin_handle();
            std::cout << "Input skin:\n";
            size_t len = getline(&skin, &lim, stdin);

            if (len > 0 && skin[len - 1] == '\n') {
                skin[len - 1] = '\0';
            }

            if (std::regex_match(skin, pattern)) {
                break;
            }

            std::cout << "white, black, or colored.\n(Usage: only lowercase characters!)\n";
        }

        return skin;
    }

    char get_gender() {
        char c;

        for ( ;; ) {
            std::cout << "Input gender:\n";
            std::cin >> c;
            if (c == 'M' || c == 'm' || c == 'W' || c == 'w')
                break;
            std::cout << "[M/m] == man, [W/w] = woman\n";
        }

        return c;
    }

    
}

namespace my {

    

    unsigned int get_num(int a, int b) {

        int n;
        while (!(std::cin >> n) || (n < a || n > b)) {
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
                delete[] name; 
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

    my::human::human(const human& other) : gender_(other.gender_), height_(other.height_), age_(other.age_), salary_(other.salary_), n_div_(other.n_div_) {
        name_ = strdup(other.name_);
        character_ = strdup(other.character_);
        skin_ = strdup(other.skin_);
    }

    my::human& my::human::operator=(const human& other) {
        if (this != &other) {
            delete [] name_;
            delete [] character_;
            delete [] skin_;

            gender_ = other.gender_;
            height_ = other.height_;
            age_ = other.age_;
            salary_ = other.salary_;
            n_div_ = other.n_div_;
            name_ = strdup(other.name_);
            character_ = strdup(other.character_);
            skin_ = strdup(other.skin_);
        }
        return *this;
    }

    my::human::~human() {
        delete [] name_;
        delete [] character_;
        delete [] skin_;
    }
   
    my::human create_human() {
        my::human human;
        human.name_ = get_name();
        human.gender_ = get_gender();

        std::cout << "Input: heigth, age, salary and number of divorces:\n";
        human.height_ = get_num();
        human.age_ = get_num();
        human.salary_ = get_num();
        human.n_div_ = get_num();

        human.character_ = get_character();
        human.skin_ = get_skin();

        return human;
    }

    void add_human(const char* name) {
        std::ofstream file(name, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "File was not opened!\n";
            return;
        }

        my::human human = create_human();

        file << human.name_ << ' ' << human.gender_ << ' ' << human.height_
            << ' ' << human.age_ << ' ' << human.character_ << ' ' << human.skin_
            << ' ' << human.salary_ << ' ' << human.n_div_;
        
        file.close();
    }

    void erase_human(const char* file, const char* name) {
        std::ifstream inFile(file, std::ios::binary);
        std::ofstream tempFile("temp.dat", std::ios::binary);

        if (!tempFile.is_open() || !inFile.is_open()) {
            std::cerr << "Error opening files." << std::endl;
            return;
        }

        my::human record;
        bool found = false;

        while (inFile >> record) {
            if (strcmp(record.name_, name) != 0) {
                if (record.name_[0] != '\n')
                    tempFile << record;
            } else {
                found = true;
            }
        }

        tempFile.close();
        inFile.close();

        if (!found) {
            std::cout << "There is no human with that name!\n";
            return;
        }

        remove(file);
        rename("temp.dat", file);
    }

    void find(const char* file, int val) {
        std::ifstream in(file, std::ios::binary);

        if (!in.is_open()) {
            std::cerr << "Failed to open the file!\n";
            return;
        }

        const int SIZE = 100;
        my::human arr[SIZE];
        int i = 0;

        while (in >> arr[i++]);

        in.close();

        for (int j = 0; j < i - 1; ++j) {
            for (int k = j + 1; k < i - 1; ++k) {
                if (arr[j].gender_ != arr[k].gender_ &&
                        arr[j].name_[0] != '\n' && arr[k].name_[0] != '\n' &&
                        arr[j].name_[0] == arr[k].name_[0] &&
                        arr[j].salary_ + arr[k].salary_ >= val) {
                    std::cout << arr[j];
                    std::cout << arr[k];
                }
            }
        }
    }


    void print_agency(const char* file) {
        std::ifstream in(file, std::ios::binary);
        if (!in.is_open()) {
            std::cerr << "Failed to open file\n";
            return;
        }

        my::human tmp;
        while (in >> tmp) {
            std::cout << tmp;
        }

        in.close();
    }
    
    std::istream& operator>>(std::istream& is, my::human& h) {
        const int maxStringLength = 100;

        char name[maxStringLength];
        char character[maxStringLength];
        char skin[maxStringLength];

        is.getline(name, maxStringLength, ' ');

        is >> h.gender_ >> h.height_ >> h.age_;

        is.ignore();
        is.getline(character, maxStringLength, ' ');
        is.getline(skin, maxStringLength, ' ');

        is >> h.salary_ >> h.n_div_;

        delete [] h.name_;
        delete [] h.character_;
        delete [] h.skin_;

        h.name_ = new char[strlen(name) + 1];
        strcpy(h.name_, name);

        h.character_ = new char[strlen(character) + 1];
        strcpy(h.character_, character);

        h.skin_ = new char[strlen(skin) + 1];
        strcpy(h.skin_, skin);

        return is;
    }

    std::ostream& operator<<(std::ostream& os, const my::human& h) {
        os << (h.name_ ? h.name_ : "N/A") << ' ';
        os << h.gender_ << ' ';
        os << h.height_ << ' ';
        os << h.age_ << ' ';
        os << (h.character_ ? h.character_ : "N/A") << ' ';
        os << (h.skin_ ? h.skin_ : "N/A") << ' ';
        os << h.salary_ << ' ';
        os << h.n_div_ << std::endl;

        return os;
    }
}
