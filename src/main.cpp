#include "main.h"

#include <iostream>

#include "search.h"

using namespace std;

int g_size_of_seq = 0;

int g_func_to_test_num = 0;
// 0 - Jump search
// 1 - Jump two-level search
// 2 - Binary search
// 3 - Interpolation search

int g_situation_of_search = 0;
// 0 - does not exist
// 1 - value from start
// 2 - value from center
// 3 - value from end

int g_amount_of_comparations = 0; 

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Not correct amount of command line params\n";
    } else {
        g_size_of_seq = atoi(argv[1]);
        g_func_to_test_num = atoi(argv[2]);
        if (g_size_of_seq > 0 && g_func_to_test_num >= 0 && g_func_to_test_num <= 2 &&
            g_situation_of_search >= 0 && g_situation_of_search <= 3) {
            Tests();
        }
    }
    return 0;
}

void Tests() {
    int step = g_size_of_seq / 2;
    for (int i = 0; i < TEST_CASES_NUM; i++) {
        cout << g_size_of_seq << '\t';
        for (int j = 0; j < SITUATIONS_OF_SEARCH_AMOUNT; j++) {
            g_situation_of_search = j;
            int* sequence = (int*)calloc(g_size_of_seq, sizeof(int));
            IntegerSortedSquenceGen(sequence, g_size_of_seq);
            TestingFunction(sequence, g_size_of_seq);
            free(sequence);
            cout.flush();
        }
        cout << "\n";
        g_size_of_seq += step;
    }
}

void TestingFunction(int* data, int size) {
    int to_search = 0;
    switch (g_situation_of_search) {
        case 0:
            to_search = -1;
            break;
        case 1:
            to_search = data[g_size_of_seq / 10];
            break;
        case 2:
            to_search = data[size / 2];
            break;
        case 3:
            to_search = data[g_size_of_seq - (g_size_of_seq / 10)];
            break;
        default:
            break;
    }
    g_amount_of_comparations = 0;
    switch (g_func_to_test_num) {
    case 0:
        JumpSearch(data, to_search, size);
        cout << g_amount_of_comparations << "\t";
        break;
    case 1:
        JumpSearch2ndLevel(data, to_search, size);
        cout << g_amount_of_comparations << "\t";
        break;
    case 2:
        BinarySearch(data, to_search, size);
        cout << g_amount_of_comparations << "\t";
        break;
    case 3:
        InterpolationSearch(data, 0, size - 1, to_search);
        cout << g_amount_of_comparations << "\t";
        break;
    default:
        break;
    }
}

void IntegerSortedSquenceGen(int *sequence, int lenght) {
    for (int i = 0; i < lenght; i++) {
        sequence[i] = i;
    }
}

// Searching algorythms

int JumpSearch(int* data, int x, int size) {
    // Finding block size to be jumped
    int step = step(size);

    // Finding the block where element is
    // present (if it is present)
    int prev = 0;
    while (data[min(step, size) - 1] < x) {
        g_amount_of_comparations++;
        prev = step;
        step += step(size);
        if (prev >= size) return -1;
    }
    g_amount_of_comparations++;

    // Doing a linear search for x in block
    // beginning with prev.
    while (data[prev] < x) {
        prev++;
        g_amount_of_comparations++;

        // If we reached next block or end of
        // array, element is not present.
        if (prev == min(step, size)) return -1;
    }
    g_amount_of_comparations += 2;
    // If element is found
    if (data[prev] == x) return prev;

    return -1;
}

int JumpSearch2ndLevel(int* data, int x, int size) {
    int step = sqrt(size);

    int prev = 0;
    while (data[min(prev + step, size) - 1] < x) {
        g_amount_of_comparations++;
        prev += step;
        if (prev >= size) return -1;
    }
    g_amount_of_comparations++;

    return JumpSearch(data + prev, x, step);
}

int BinarySearch(int* data, int x, int size) {
    int l = 0;
    int r = size - 1;
    int mid;

    while (l <= r) {
        mid = l + (r - l) / 2;
        g_amount_of_comparations++;
        if (data[mid] == x) return mid;
        g_amount_of_comparations++;
        if (data[mid] < x) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return -1;
}

int InterpolationSearch(int* data, int lo, int hi, int x) {
    int pos;

    // Since array is sorted, an element present
    // in array must be in range defined by corner
    if (lo <= hi && x >= data[lo] && x <= data[hi]) {
        // Probing the position with keeping
        // uniform distribution in mind.
        pos = lo + (((double)(hi - lo) / (data[hi] - data[lo])) * (x - data[lo]));

        g_amount_of_comparations++;
        // Condition of target found
        if (data[pos] == x) {
            return pos;
        }

        g_amount_of_comparations++;
        if (data[pos] < x) {
            // If x is larger, x is in right sub array
            return InterpolationSearch(data, pos + 1, hi, x);
        } else {
            // If x is smaller, x is in left sub array
            return InterpolationSearch(data, lo, pos - 1, x);
        }
    }
    return -1;
}