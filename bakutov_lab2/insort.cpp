#include "insort.h"

namespace my {
    void insort(float arr[], int n, bool asc) {
        for (int step = 1; step < n; ++step) {
            float key = arr[step];
            int j = step - 1;

            if (asc) {
                while (j >= 0 && key < arr[j]) {
                    arr[j + 1] = arr[j];
                    --j;
                }
            } else {
                while (j >= 0 && key > arr[j]) {
                    arr[j + 1] = arr[j];
                    --j;
                }
            }
            arr[j + 1] = key;
        }
    }
} //namespace my
