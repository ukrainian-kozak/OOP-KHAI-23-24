#include "vector.h"
#include <iostream>
#include <string>
#include <cassert>

int main() {
    my::vector<int> vec(10); //set capacity
    
    vec.insert(vec.begin(), vec.end(), vec.begin());
    assert(vec.size() == 0);
    assert(vec.capacity() == 10);
    
    vec.insert(1, vec.begin());
    assert(vec[0] == 1);

    vec[0] = 2;
    assert(vec[0] == 2);

    vec.erase(vec.begin());
    assert(vec.size() == 0);

    vec.push_back(3);
    assert(vec.size() == 1);
    assert(vec[0] == 3);
    
    my::vector<int> to_insert = {1,2,3,4,5};
    vec.insert(to_insert.begin(), to_insert.end(), vec.begin());
    vec.insert(to_insert.begin(), to_insert.end(), vec.end());
    vec.insert(to_insert.begin(), to_insert.end(), vec.begin() + 5);
    for (auto& it: vec)
        std::cout << it << ' ';
    std::cout << std::endl;

    vec.erase(vec.begin(), vec.begin() + 5);
    for (auto& it: vec)
        std::cout << it << ' ';
    std::cout << std::endl;

    vec.add_vector(to_insert.begin(), to_insert.end());

    for (auto& it: vec)
        std::cout << it << ' ';
    std::cout << std::endl;
    
    vec.sort(0, vec.size());
    for (auto& it: vec)
        std::cout << it << ' ';
    std::cout << std::endl;

    my::vector<int> for_find = {1,1,1,2};
    auto res = vec.find(for_find);
    std::cerr << typeid(res).name();
    std::cerr << typeid(vec.begin()).name();
    assert(res == vec.begin());
    
    auto res2 = vec.find(1);
    assert(*res2 == 1);

    assert(vec.count(1) == 3);
}
