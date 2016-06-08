
/*
 7_2. Заявки на переговоры.
 В большой IT-фирме есть только одна переговорная комната. Желающие посовещаться заполняют заявки с желаемым временем начала и конца. Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
 Число заявок ≤ 100000.
 Формат входных данных:
 Вход содержит только пары целых чисел — начала и концы заявок.
 Формат выходных данных:
 Выход должен содержать натуральное число — максимальное число заявок.
 */



#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct hours {
    int begin;
    int end;
    
    bool operator < (const hours &item)
    const
    {
        return ( this -> end < item.end);
    }
};

class table{
private:
    int size;
    int capacity;
    hours *arr;
public:
    table()
    {
        size = 0;
        capacity = 4;
        arr = new hours[8];
    }
    
    int get_size()
    {
        return size;
    }
    
    void push(hours a)
    {
        if (size == capacity)
        {
            increase();
        }
        arr[size++] = a;
    }
    
    void increase()
    {
        capacity *= 2;
        hours *tmp = new hours[capacity];
        for (int i = 0; i < size; i++)
        {
            tmp[i] = arr[i];
        }
        delete[]arr;
        arr = tmp;
    }
    
    const hours &operator[](int index)
    {
        return arr[index];
    }
    
    void sort1()
    {
        sort(arr, arr + size);
    }
    
    ~table()
    {
        delete[] arr;
    }
};


int solve(table &time)
{
    int  kol = 1;
    time.sort1();
    int max = 0;
    for (int i = 1; i < time.get_size(); i++)
    {
        if (time[i].begin >= time[max].end)
        {
            kol++;
            max = i;
        }
    }
    return kol;
}

int main() {
    
    table time;
    hours buffer;
    do{
        cin >> buffer.begin >> buffer.end;
        time.push(buffer);
    } while (!cin.eof());
    
    cout << solve(time);
    return 0;
}