/* #include <cstdlib> // rand() and srand()
#include <ctime>   // use time() to set seed for srand()
#include <iostream>

void PrintArray(int *arr)
{
    int size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
}
int *Shuffle(int *arr, int n)
{
    if (n > 1)
    {
        int i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++)
        {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = arr[j];
            arr[j] = arr[i];
            arr[i] = t;
        }
    }
    PrintArray(arr);
    return arr;
}

int *MakeNewArray(int *arr, int size)
{
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = i;
    }
    return arr;
}
 */