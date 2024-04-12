#include <sys/types.h>

#define MINIMAL_VALUE 1
#define MAXIMAL_VALUE 1e5

typedef void (*Test)(void);

void Tests();
void TestJump(int *data, int size);
void GenerateRandomSequence(int *data, size_t size, int min_value, int max_value);