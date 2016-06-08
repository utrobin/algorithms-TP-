
/*
 Дан массив целых чисел А[0..n­1]. Известно, что на интервале [0, m] значения массива строго
 возрастают, а на интервале [m, n­1] строго убывают. Найти m за O(log m).
 n ≤ 10000.
 T(n) = O (log m), M(n) = O(n)
 */

#include <iostream>
#include <cassert>

using namespace std;

int binar(const int *a, int first, int last)      // бинарный поиск
{
    assert (a != NULL);
    while(first < last)
    {
        int mid = (first + last) / 2;
        if (a[mid] < a[mid + 1])
        {
            first = mid + 1;
        }
        else
        {
            last = mid;
        }
    }
        return first;
}

int log(const int *a, int n)                  // функция поиска интервала
{
    assert (n > 0 && a != NULL);
    if (n == 1) return 0;
    if (n == 2)
    {
        return a[0] > a[1] ? 0 : 1;
    }
    
    int first = 0, mid = 1, last = 2;
    
    while (last < n)
    {
        if (a[last] < a[mid])
        {
            a[mid + 1] > a[mid] ? first = mid : last = mid;
            return binar(a, first, last);
        }
        first = mid; mid = last; last *= 2;
    }
    
    if (a[mid + 1] > a[mid])
    {
        return binar(a, mid, n - 1);
    }
    else
    {
        return binar(a, first, mid);
    }
}

int main()
{
    int n =  0;
    cin >> n;
    assert (n > 0 && n < 10000);
    int *array = new int [n];
    for (int i = 0; i < n; ++i)
    {
        cin >> array[i];
    }
    cout << log(array, n);
    delete [] array;
    return 0;
}