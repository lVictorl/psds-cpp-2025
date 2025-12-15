#include <stdexcept>

<<<<<<< HEAD
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
=======

void SwapPtr(/* write arguments here */) {
    throw std::runtime_error{"Not implemented"};
>>>>>>> 4477f12d1d360b59708503f7b0b325acb0c5bc52
}