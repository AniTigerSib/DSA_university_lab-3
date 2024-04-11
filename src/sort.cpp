#include "sort.h"

void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void MSD(int* data, int size) {
    int i = 0;
    uint Mask = 0;
    for (i = 0; i < size; i++) {
        Mask |= (uint)data[i];
    }
    for (i = 31; i >= 1; i--) {
        if (Mask & (1 << i)) {
            break;
        }
    }
    MSRadix(data, 0, size - 1, 1 << i);
}

void MSRadix(int* data, int low, int high, uint Mask) {
    if (Mask > 0 && low < high) {
        int i = MSDPatrition(data, low, high, Mask);
        MSRadix(data, low, i - 1, Mask >> 1);
        MSRadix(data, i, high, Mask >> 1);
    }
}

int MSDPatrition(int* data, int low, int high, uint Mask) {
    int i = low - 1;
    int j = high + 1;
    while (true) {
        while ((!(Mask & (uint)data[++i])) && i < high);
        while (((Mask & (uint)data[--j])) && j > low);
        if (i >= j) break;
        Swap(data[i], data[j]);
    }
    return (i == j && i == high) ? ++i : i;
}