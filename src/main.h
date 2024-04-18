#include <sys/types.h>

#define TEST_CASES_NUM 19
#define SITUATIONS_OF_SEARCH_AMOUNT 4
#define MINIMAL_VALUE 1
#define MAXIMAL_VALUE 1e8
#define step(x) sqrt(x)

typedef int (*Test)(int*, int, int);

void Tests();
void TestingFunction(int* data, int size);
void IntegerSortedSquenceGen(int *sequence, int lenght);