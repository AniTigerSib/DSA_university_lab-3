#include <sys/types.h>

#define MINIMAL_VALUE 1
#define MAXIMAL_VALUE 1e5

typedef int (*Test)(int*, int, int);

void Tests();
void TestingFunction(int* data, int size, Test func_to_test);
void GenerateRandomSequence(int *data, size_t size, int min_value, int max_value);