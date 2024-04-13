#include "main.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <random>

#include "search.h"
#include "sort.h"

using namespace std;

int g_size_of_seq = 0;

int g_func_to_test_num = 0;
// 0 - Jump search
// 1 - Binary search
// 2 - Interpolation search

int g_situation_of_search = 0;
// 0 - does not exist
// 1 - value from start
// 2 - value from center
// 3 - value from end

int g_amount_of_comparations = 0;

const Test g_functions_to_test[] = {JumpSearch, BinarySearch, InterpolationSearch};

int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "Not correct amount of command line params\n";
    } else {
        g_size_of_seq = atoi(argv[1]);
        g_func_to_test_num = atoi(argv[2]);
        g_situation_of_search = atoi(argv[3]);
        if (g_size_of_seq > 0 && g_func_to_test_num >= 0 && g_func_to_test_num <= 2 && g_situation_of_search >= 0 &&
            g_situation_of_search <= 3) {
            Tests();
        }
    }
    return 0;
}

void Tests() {
    int* sequence = (int*)calloc(g_size_of_seq, sizeof(int));
    GenerateRandomSequence(sequence, g_size_of_seq, MINIMAL_VALUE, MAXIMAL_VALUE);
    MSD(sequence, g_size_of_seq);
    TestingFunction(sequence, g_size_of_seq, g_functions_to_test[g_func_to_test_num]);
    free(sequence);
}

void TestingFunction(int* data, int size, Test func_to_test) {
    int to_search = 0;
    switch (g_situation_of_search) {
        case 0:
            to_search = -1;
            break;
        case 1:
            to_search = data[0];
            break;
        case 2:
            to_search = data[size / 2];
            break;
        case 3:
            to_search = data[size - 1];
            break;
        default:
            break;
    }
    g_amount_of_comparations = 0;
    cout << func_to_test(data, to_search, size) << "\n" << g_amount_of_comparations << "\n";
}

void GenerateRandomSequence(int* data, size_t size, int min_value, int max_value) {
    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());

    // Распределение
    using Dist = std::uniform_int_distribution<int>;

    Dist dist(min_value, max_value);

    // Генерация случайных чисел
    for (size_t i = 0; i < size; ++i) {
        data[i] = dist(gen);
    }

    // Перемешивание
    std::shuffle(data, data + size, gen);
}

// Searching algorythms

int JumpSearch(int* data, int x, int size) {
    // Finding block size to be jumped
    int step = sqrt(size);

    // Finding the block where element is
    // present (if it is present)
    int prev = 0;
    while (data[min(step, size) - 1] < x) {
        g_amount_of_comparations++;
        prev = step;
        step += sqrt(size);
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