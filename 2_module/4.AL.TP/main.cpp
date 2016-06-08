
/*
 
 4_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <iostream>

using namespace std;

int partition(int *array, int start, int end)
{
    if (start == end)
        return start;
    
    int pivot = rand() % (end - start) + start;
    swap(array[pivot], array[end]);
    pivot = end;
    int i = start;
    int j = i;
    while ( j < end )
    {
        if (array[j] <= array[pivot])
        {
            swap(array[j], array[i]);
            i++;
            j++;
        }
        while (array[j] > array[pivot])
            j++;
    }
    swap(array[i], array[pivot]);
    pivot = i;
    return pivot;
}


int find_k(int *arr, int size, int k)
{
    int start = 0, end = size - 1;
    int p;
    do
    {
        p = partition(arr, start, end);
        if ( k > p )
            start = p + 1;
        if ( k < p )
            end = p - 1;
    }
    while (p != k);
    return arr[k];
}

int main()
{
    int size,k;
    cin >> size >> k;
    
    int *array = new int[size];
    for (int i = 0; i < size; i++)
        cin >> array[i];
    
    cout << find_k(array, size, k);
    
    delete[] array;
    return 0;
}