#pragma once

#include <cstddef>
#include <cstring>

namespace my {
    class priority_queue {
        public:
            priority_queue() : arr_(nullptr), size_(0), cap_(5) {}
            priority_queue(int n) : arr_(new int[n]), size_(0), cap_(n) {}
            priority_queue(const priority_queue&) = delete;
            priority_queue(priority_queue&&) = delete;
            priority_queue& operator=(const priority_queue&) = delete;
            priority_queue& operator=(priority_queue&&) = delete;
            ~priority_queue();

        public:
            void push(int val);
            void pop();
            bool empty() const;
            int top() const;
            size_t size() const;
            void resize(int n);

        private:
            int* arr_;
            size_t size_;
            size_t cap_;
            
            void heapify();
            void heapify_down(int index);
    };
    
}
