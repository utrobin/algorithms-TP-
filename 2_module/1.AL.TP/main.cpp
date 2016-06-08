
/*
 Во всех вариантах данной задачи необходимо реализовать и использовать с ортировку вставками.
 1_1. Ящики.
 На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку поступления от 0. Известно, что их все можно сложить один в один (то есть так, что каждый следующий помещается в предыдущий). Один ящик можно вложить в другой, если его можно перевернуть так, что размеры одного ящика по всем осям станут строго меньше размеров другого ящика по соответствующим осям. Требуется определить, в какой последовательности они будут вложены друг в друга. Вывести номера ящиков.
 */

#include <iostream>
using namespace std;

struct box
{
    int summa;
    int coint;
    
    bool operator > (const box &item)
    const
    {
        return ( this -> summa > item.summa);
    }
};

void sort (box *array, int n)
{
    box temp;
    int previous;
    for (int i = 1; i < n; i++)
    {
        temp = array[i];
        previous = i - 1;
        while ( previous >= 0 && array[previous] > temp )
        {
            array[previous+1] = array[previous];
            previous--;
        }
        array[previous+1] = temp;
    }
}

int main()
{
    int n;
    cin >> n;
    box *array = new box[n];
    int coint = 0;
    
    while (coint < n)
    {
        int x,y,z;
        cin >> x >> y >> z;
        int summa;
        summa = x + y + z;
        array[coint].summa = summa;
        array[coint].coint = coint;
        coint++;
    }
    
    sort (array, n);
    for ( int i = 0; i < n; i++ )
        cout << array[i].coint << " ";
    
    delete [] array;
    return 0;
}