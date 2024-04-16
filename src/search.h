#ifndef SEARCH_H
#define SEARCH_H

#include <cmath>

#define min(a,b) ((a) < (b) ? (a) : (b))

int JumpSearch(int* data, int x, int size);
int JumpSearch2ndLevel(int* data, int x, int size);
int BinarySearch(int* data, int x, int size);
int InterpolationSearch(int* data, int lo, int hi, int x);

#endif