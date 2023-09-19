#include "priority_queue.h"

namespace {
    void swap(int& a, int& b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
}

namespace my {
    my::priority_queue::~priority_queue() {
        delete [] arr_;
    }

    void my::priority_queue::resize(int n) {
        if (n <= cap_) {
            return;
        }

        int* narr = new int[cap_ * 2];
        memcpy(narr, arr_, size() * sizeof(int));
        cap_ *= 2;

        delete [] arr_;
        arr_ = narr;
    }

    void my::priority_queue::push(int val) {
        resize(size_ + 1);
        arr_[size_] = val;
        ++size_;
        heapify();
    }

    void my::priority_queue::pop() {
        if (empty())
            throw "Heap is empty";

        arr_[0] = arr_[--size_];
        heapify();
    }

    bool my::priority_queue::empty() const {
        return size() == 0;
    }

    int my::priority_queue::top() const {
        return arr_[0];
    }

    size_t my::priority_queue::size() const {
        return size_;
    }

    void my::priority_queue::heapify() {
        for (int i = (size() / 2) - 1; i >= 0; --i) {
            heapify_down(i);
        }
    }

    void my::priority_queue::heapify_down(int index) {
        int largest = index;
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;

        if (left_child < size() && arr_[left_child] > arr_[largest])
            largest = left_child;
        if (right_child < size() && arr_[right_child] > arr_[largest])
            largest = right_child;

        if (largest != index) {
            swap(arr_[index], arr_[largest]);
            heapify_down(largest);
        }
    }

}
