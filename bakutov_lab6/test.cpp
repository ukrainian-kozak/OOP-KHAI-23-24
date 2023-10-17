#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1,2,3,4,5,0,0,0,0,0,0};
    int dist = 5;

    for (int i = v.size() - 1; i >= 2; ++i) {
        v[i + dist] = v[i];
    }

    for (auto& it: v)
        std::cout << it << ' ';
    return 0;
}
