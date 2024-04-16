#include "search.h"

int JumpSearch(int* data, int x, int size) {
    // Finding block size to be jumped
    int step = sqrt(size);

    // Finding the block where element is
    // present (if it is present)
    int prev = 0;
    while (data[min(step, size) - 1] < x) {
        prev = step;
        step += sqrt(size);
        if (prev >= size) return -1;
    }

    // Doing a linear search for x in block
    // beginning with prev.
    while (data[prev] < x) {
        prev++;

        // If we reached next block or end of
        // array, element is not present.
        if (prev == min(step, size)) return -1;
    }
    // If element is found
    if (data[prev] == x) return prev;

    return -1;
}

int JumpSearch2ndLevel(int* data, int x, int size) {
    int step = sqrt(size);

    int prev = 0;
    while (data[min(prev + step, size) - 1] < x) {
        prev += step;
        if (prev >= size) return -1;
    }

    return JumpSearch(data + prev, x, step);
}

int BinarySearch(int* data, int x, int size) {
    int l = 0;
    int r = size - 1;
    int mid;

    while (l <= r) {
        mid = l + (r - l) / 2;

        if (data[mid] == x) return mid;

        if (data[mid] < x) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return -1;
}

int InterpolationSearch(int* data, int x, int size) {
    int l = 0;
    int r = size - 1;
    int pos = l + x * (r - l) / (data[r] - data[l]);
    for (; l <= r; pos = l + data[pos] * (r - l) / (data[r] - data[l])) {
        if (data[pos] == x) return pos;
        
        if (x < data[pos]) {
            r = pos - 1;
        } else {
            l = pos + 1;
        }
    }
    return -1;
}