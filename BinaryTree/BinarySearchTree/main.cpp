#include <iostream> // cout, <<, endl
#include <cstdlib>  // rand() and srand()
#include <ctime>    // use time() to set seed for srand()
#include <chrono>   // C++ library used to measure execution time
#include "BinaryTree.h"
#include "Gen.h"
int main()
{

    BinaryTree<int> B;
    int array[100];
    int size = sizeof(array) / sizeof(array[0]);
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }
    for (int i = 0; i < size; i++)
    {
        B.Insert(array[i]);
    }
    B.Inorder(std::cout);
    B.Search(222);
}
