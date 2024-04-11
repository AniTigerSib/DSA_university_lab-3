#ifndef SORT_H
#define SORT_H

#include <sys/types.h>

void Swap(int& a, int& b);
void MSD(int* data, int size);
void MSRadix(int* data, int low, int high, uint Mask);
int MSDPatrition(int* data, int low, int high, uint Mask);

#endif