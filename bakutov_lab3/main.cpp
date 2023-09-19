#include <iostream>
#include <limits>
#include "priority_queue.h"

namespace {

    int get_num() {
        int n;
        while (!(std::cin >> n)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Incorrect input\n";
        }
        return n;
    }

    void get_data(const int& n, my::priority_queue& pq) {
       
        for (int i = 0; i < n; ++i) {
            pq.push(get_num());
        }
    }

    int stones(my::priority_queue& pq) {
        while (pq.size() > 1) {
            int y = pq.top();
            pq.pop();
            int x = pq.top();
            pq.pop();
            if (y > x)
                pq.push(y - x);
        }
        return pq.empty() ? 0 : pq.top();
    }

}

int main() {
    int n = get_num();
    my::priority_queue pq(n);
    get_data(n, pq);
    std::cout << "Min weight between two bunches: " << stones(pq) << std::endl;
    return 0;
}
