#include "main.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <random>
#include <string>

#include "search.h"
#include "sort.h"

using namespace std;

int g_size_of_seq = 0;

int g_func_to_test = 0;
// 0 - Jump search
// 1 - Binary search
// 2 - Interpolation search

int g_situation_of_search = 0;
// 0 - does not exist
// 1 - value from start
// 2 - value from center
// 3 - value from end

int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "Not correct amount of command line params\n";
    } else {
        g_size_of_seq = atoi(argv[1]);
        g_func_to_test = atoi(argv[2]);
        g_situation_of_search = atoi(argv[3]);
        if (g_size_of_seq > 0 && g_func_to_test >= 0 && g_func_to_test <= 2 && g_situation_of_search >= 0 && g_situation_of_search <= 3) {
            Tests();
        }
    }
}

void Tests() {
    int* sequence = (int*)calloc(g_size_of_seq, sizeof(int));
    GenerateRandomSequence(sequence, g_size_of_seq, MINIMAL_VALUE, MAXIMAL_VALUE);
    switch (g_func_to_test) {
    case 0:
        TestJump(sequence, g_size_of_seq);
        break;
    case 1:
        break;
    case 2:
        break;
    default:
        break;
    }
    free(sequence);
}

void TestJump(int *data, int size) {
    int to_search = 0;
    
}

void GenerateRandomSequence(int *data, size_t size, int min_value, int max_value) {
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