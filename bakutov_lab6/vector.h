#pragma once

#include "allocator.h"
#include <type_traits>
#include <memory>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <iostream>
    namespace my {

        //Iterator.
        template<typename T>
            class iterator {
                public:
                    using iterator_category = std::random_access_iterator_tag;
                    using difference_type = std::ptrdiff_t;
                    using value_type = T;
                    using pointer = value_type*;
                    using reference = value_type&;

                public:
                    constexpr iterator(pointer ptr): ptr_(ptr) {}

                    reference operator*() const {
                        return *ptr_;
                    }
                    pointer operator->() {
                        return ptr_;
                    }

                    iterator& operator++() {
                        ++ptr_;
                        return *this;
                    }
                    iterator operator++(int) {
                        iterator temp = *this;
                        ++ptr_;
                        return temp;
                    }
                    iterator& operator+=(difference_type n) {
                        ptr_ += n;
                        return *this;
                    }
                    iterator& operator-=(difference_type n) {
                        ptr_ -= n;
                        return *this;
                    }
                    iterator& operator--() {
                        --ptr_;
                        return *this;
                    }
                    iterator operator--(int) {
                        iterator temp = *this;
                        --ptr_;
                        return temp;
                    }
                    iterator operator+(difference_type n) {
                        iterator temp = *this;
                        temp.ptr_ += n;
                        return temp;
                    }
                    difference_type operator-(const iterator& other) const {
                        return ptr_ - other.ptr_;
                    }

                    iterator operator-(difference_type count) {
                        iterator temp = *this;
                        temp.ptr_ -= count;
                        return temp;
                    }

                    bool operator<(const iterator& rhz) const {
                        return ptr_ < rhz.ptr_;
                    }
                    bool operator==(const iterator& rhz) const {
                        return ptr_ == rhz.ptr_;
                    }
                    bool operator!=(const iterator& rhz) const {
                        return ptr_ != rhz.ptr_;
                    }
                    bool operator>(const iterator& rhz) const {
                        return ptr_ > rhz.ptr_;
                    }
                    bool operator<=(const iterator& rhz) const {
                        return !(ptr_ > rhz.ptr_);
                    }
                    bool operator>=(const iterator& rhz) const {
                        return !(ptr_ < rhz.ptr_);
                    }



                private:
                    T* ptr_;
            };


        template<typename T, typename Allocator = my::allocator<T>>
            class vector {

                private:
                    size_t size_;
                    size_t cap_;
                    T* arr_;
                    Allocator alloc_;

                public:
                    using iter = iterator<T>;
                    using const_iter = iterator<const T>;
                    using reverse_iter = std::reverse_iterator<iter>;
                    using const_reverse_iter = std::reverse_iterator<const_iter>;

                public:
                    using allocator_type = Allocator;
                    using value_type = T;
                    using size_type = size_t;
                    using pointer = T*;
                    using reference = T&;
                    using const_pointer = const T*;
                    using const_reference = const T&;

                public:

                    // Iterator methods.

                    iter begin() {
                        return iter(arr_);
                    }

                    const_iter begin() const {
                        return const_iter(arr_);
                    }

                    iter end() {
                        return iter(arr_ + size_);
                    }

                    const_iter end() const {
                        return const_iter(arr_ + size_);
                    }

                    const_iter cbegin() const {
                        return const_iter(arr_);
                    }

                    const_iter cend() const {
                        return const_iter(arr_ + size_);
                    }

                    reverse_iter rbegin() {
                        return reverse_iter(end());
                    }

                    const_reverse_iter rbegin() const {
                        return const_reverse_iter(end());
                    }

                    reverse_iter rend() {
                        return reverse_iter(begin());
                    }

                    const_reverse_iter rend() const {
                        return const_reverse_iter(begin());
                    }

                    const_reverse_iter rcbegin() const {
                        return const_reverse_iter(end());
                    }

                    const_reverse_iter rcend() const {
                        return const_reverse_iter(begin());
                    }



                    // Constructors.

                    constexpr vector(const Allocator& alloc = Allocator()): size_(0), cap_(5), arr_(nullptr), alloc_(alloc) {
                        arr_ = std::allocator_traits<allocator_type>::allocate(alloc_, cap_);
                    }

                    constexpr vector(size_t count, const T& value, const Allocator& alloc = Allocator()): 
                        size_(count), cap_(count * 2), arr_(nullptr), alloc_(alloc) {
                            arr_ = std::allocator_traits<allocator_type>::allocate(alloc_, count);

                            for (size_t i = 0; i < count; ++i) {
                                std::allocator_traits<allocator_type>::construct(alloc_, arr_ + i, value);
                            }
                        }

                    constexpr vector(size_t count, const Allocator& alloc = Allocator()):
                        size_(0), cap_(count), arr_(nullptr), alloc_(alloc) {
                            arr_ = std::allocator_traits<allocator_type>::allocate(alloc_, count);
                        }

                    constexpr vector(const vector& other):
                        size_(other.size_), cap_(other.cap_), arr_(nullptr), alloc_(other.alloc_) {
                            arr_ = std::allocator_traits<allocator_type>::allocate(alloc_, cap_);
                            std::copy(other.cbegin(), other.cend(), begin());
                        }

                    constexpr vector(vector&& other):
                        size_(other.size_), cap_(other.cap_), arr_(other.arr_), alloc_(std::move(other.alloc_)) {
                            other.size_ = 0;
                            other.cap_ = 0;
                            other.arr_ = nullptr;
                        }

                    constexpr vector(std::initializer_list<T> init, Allocator alloc = Allocator()):
                        size_(init.size()), cap_(init.size() * 2), arr_(nullptr), alloc_(alloc) {
                            arr_ = std::allocator_traits<allocator_type>::allocate(alloc_, cap_);
                            std::uninitialized_copy(init.begin(), init.end(), begin());
                        }

                    // Assignments.


                    constexpr vector& operator=(const vector& other) {
                        if (*this == &other)
                            return *this;

                        reserve(other.size());
                        std::copy(other.cbegin(), other.cend(), begin());

                        return *this;
                    }

                    constexpr vector& operator=(vector&& other) {
                        clear();

                        size_ = other.size_;
                        cap_ = other.cap_;
                        arr_ = other.arr_;
                        alloc_ = std::move(other.alloc_);

                        other.size_ = 0;
                        other.cap_ = 0;
                        other.arr_ = nullptr;

                        return *this;
                    }

                    constexpr vector& operator=(std::initializer_list<T> list) {
                        if (size_ <= list.size()) {
                            size_ = list.size();
                            std::uninitialized_copy(list.begin(), list.end(), begin());
                        } else {
                            reserve(list.size());
                            std::uninitialized_copy(list.begin(), list.end(), begin());
                        }

                        return *this;
                    }

                
                    //Modifiers.

                    constexpr void pop_back() {
                        --size_;
                        std::allocator_traits<allocator_type>::destroy(alloc_, arr_ + size_);
                    }

                    template <typename... Args>
                        constexpr iter emplace(const iter pos, Args&&... args) {
                            size_t pos_index = std::distance(begin(), pos);
                            auto end_before = end();

                            if (size_ >= cap_) {
                                reserve(cap_);
                            }

                            if (pos == end_before) {
                                std::allocator_traits<allocator_type>::construct(alloc_, arr_ + size_, std::forward<Args>(args)...);
                                ++size_;
                            } else {
                                std::move_backward(begin() + pos_index, end(), end() + 1);
                                iter _iter = &arr_[pos_index];

                                *_iter = std::move(T(std::forward<Args>(args)...));
                               
                                ++size_;
                            }
                            return begin() + pos_index;
                        }

                    template <typename... Args>
                        constexpr reference emplace_back(Args... args) {
                            emplace(end(), std::forward<Args>(args)...);
                            return *(arr_ + size_);
                        }

                    constexpr void push_back(const T& value) {
                        emplace_back(value);
                    }

                    constexpr void push_back(T&& value) {
                        emplace_back(std::move(value));
                    }

                    constexpr void insert(const T& value, const iter pos) {
                        emplace(pos, value);
                    }

                    constexpr void insert(T&& value, const iter pos) {
                        emplace(pos, std::move(value));
                    }

                    template <typename Input>
                        constexpr void insert(Input first, Input last, iter pos) {
                            size_t pos_index = std::distance(begin(), pos);
                            size_t dist = std::distance(first, last);
                            auto end_before = end();

                            if (dist == 0)
                                return;

                                std::cerr << "Before:";
                                for (int i = 0; i < size(); ++i)
                                    std::cerr << arr_[i];
                                std::cerr << std::endl;

                            if (size() + dist >= cap_)
                                reserve(size() + dist);

                            if (pos == end_before)
                                add_vector(first, last);
                            else {
                                for (size_t i = size() + dist - 1; i > pos_index; --i) {
                                    arr_[i] = std::move(arr_[i - dist]);
                                }
                                for (int i = 0; i < size(); ++i)
                                    std::cerr << arr_[i];
                                std::cerr << std::endl;

                                size_t i = pos_index + 1;
                                for (auto it = first; it != last; ++it) {
                                    arr_[i++] = *it;
                                }

                                size_ += dist;
                            }
                        }

                    constexpr void erase(const iter& pos) {

                        size_t pos_index = std::distance(begin(), pos);
                        for (size_t i = pos_index; i < size() - 1; ++i) {
                            arr_[i] = arr_[i + 1];
                        }

                        --size_;
                    }

                    template <typename Input>
                        constexpr void erase(Input first, Input last) {
                            size_t count = std::distance(first, last);
                            size_t start = static_cast<size_t>(first - begin());
                            size_t fin = static_cast<size_t>(last - begin());

                            for (size_t it = start; it != fin + count; ++it) {
                                arr_[it] = arr_[it + count];
                            }

                            size_ -= count;
                        }

                    template <typename Input>
                    constexpr void add_vector(Input first, Input last) {
                        for (auto it = first; it != last; ++it) {
                            push_back(*it);
                        }
                    }

                    constexpr void add_vector(my::vector<T, Allocator>&& vec) {
                        for (size_t i = 0; i < vec.size(); ++i) {
                            push_back(std::move(vec[i]));
                        }
                    }

                    template <typename Comparator = std::less<T>>
                        constexpr void sort(size_t first, size_t last, Comparator comp = Comparator()) {
                            std::sort(begin() + first, begin() + last, comp);
                        }

                    constexpr iter find(const my::vector<T, Allocator>& vec) {
                        size_t n = vec.size();

                        for (size_t i = 0; i <= n - size_; ++i) {
                            size_t j = 0;
                            while (j < n && arr_[i + j] == vec[j])
                                ++j;
                            if (j == n)
                                return iter(arr_ + i);
                        }

                        return end();
                    }

                    constexpr iter find(const T& elem) {
                        for (size_t i = 0; i < size(); ++i) {
                            if (arr_[i] == elem)
                                return iter(arr_ + i);
                        }
                        return iter(arr_ + size_);
                    }

                    constexpr int count(const T& elem) {
                        int result = 0;
                        for (size_t i = 0; i < size(); ++i) {
                            if (arr_[i] == elem)
                                ++result;
                        }
                        return result;
                    }


                    // Element access

                    constexpr value_type& operator[](size_t index) {
                        return arr_[index];
                    }

                    constexpr value_type& operator[](size_t index) const {
                        return arr_[index];
                    }

                    // Capacity

                    constexpr bool empty() const {
                        return size_ == 0;
                    }

                    constexpr size_t size() const {
                        return size_;
                    }

                    constexpr size_t capacity() const {
                        return cap_;
                    }

                    constexpr void clear() {
                        for ( ; size_ != 0; )
                            pop_back();
                        std::allocator_traits<allocator_type>::deallocate(alloc_, arr_, cap_);
                    }

                    constexpr void reserve(size_t new_cap) {
                        T* new_arr = std::allocator_traits<allocator_type>::allocate(alloc_, new_cap * 2);
                        for (size_t i = 0; i < size(); ++i) {
                            std::allocator_traits<allocator_type>::construct(alloc_, new_arr + i, arr_[i]);
                            std::allocator_traits<allocator_type>::destroy(alloc_, arr_ + i);
                        }
                        std::allocator_traits<allocator_type>::deallocate(alloc_, arr_, cap_);

                        cap_ = new_cap * 2;
                        arr_ = new_arr;
                    }

                    //Destructor.
                    
                    ~vector() {
                        while (size_ > 0)
                            pop_back();
                        std::allocator_traits<allocator_type>::deallocate(alloc_, arr_, cap_);
                    }
        };
}
