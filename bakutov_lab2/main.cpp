#include <iostream>
#include <limits>
#include "insort.h"

namespace {
    void swap(float& a, float& b) {
        float tmp = a;
        a = b;
        b = tmp;
    }

    bool get_choise() {
        char c;
        for ( ;; ) {
            std::cin >> c;
            if (c == 'y' || c == 'Y' || c == 'n' || c == 'N')
                break;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return (c == 'y' || c == 'Y');
    }

    bool get_type_sort() {
        int n;
        for ( ;; ) {
            std::cin >> n;
            if (n == 1 || n == 2)
                break;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "1 - ascending\n2 - descending\nTry again:\n";
        }
        return n == 1;
    }

    float get_num(float lb = -std::numeric_limits<float>::max(),
            float ub = std::numeric_limits<float>::max()) {
        if (lb > ub)
            swap(lb, ub);

        float n;
        std::cout << "Input a number: ";
        while (!(std::cin >> n) || ((n < lb) || (n > ub))) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, try again.\n";
        }
        return n;
    }

    void get_data(int& num, float& lb, float& ub) {
        std::cout << "Number of elements in an array:\n";
        num = static_cast<int>(get_num());
        std::cout << "Input range of arrys' numbers[from/to]:\n";
        lb = get_num();
        ub = get_num();
    }

    void fill(float* arr, const int& n, float lb, float ub) {
        for (int i = 0; i < n; ++i) {
            arr[i] = get_num(lb, ub);
        }
    }

    void fill_array(float* arr, const int& n, float lb, float ub) {
        std::cout << "Filling the array:\n";
        fill(arr, n, lb, ub);
    }

    void sort(float* arr, const int& n) {
        std::cout << "Do you want sort array by ascending or descending order?[1/2]\n";
        my::insort(arr, n, get_type_sort());
    }

    void print_array(float* arr, const int& n) {
        std::cout << "Sorted array: ";
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
    }

    void allocate(float*& arr, int n) {
        arr = new float[n];
    }

    void deallocate(float*& arr) {
        delete [] arr;
        arr = nullptr;
    }

    
} //namespace
  
int main() {
    
    int num;
    float lb, ub;
    float* arr;

    for ( ;; ) {
        get_data(num, lb, ub);
        allocate(arr, num);
        
        fill_array(arr, num, lb, ub);
        sort(arr, num);
        print_array(arr, num);
        
        deallocate(arr);

        std::cout << "Do you want to run the program one more time?[Y/n]:\n";
        if (!get_choise())
            break;
    }

    return 0;
}
