#include <stdexcept>

void SwapPtr(int *&ptr1, int *&ptr2)
{
    // throw std::runtime_error{"Not implemented"};
    int *temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}

void SwapPtr(const int *&ptr1, const int *&ptr2)
{
    const int *temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}

void SwapPtr(int **&ptr1, int **&ptr2)
{
    int **temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}