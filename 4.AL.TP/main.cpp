
/*
 Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды
 push* и pop*.
 Формат входных данных.
 В первой строке количество команд n. n ≤ 1000000.
 Каждая команда задаётся как 2 целых числа: a b.
 a = 1 ­ push front
 a = 2 ­ pop front
 a = 3 ­ push back
 a = 4 ­ pop back
 Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
 Если дана команда pop*, то число b ­ ожидаемое значение.Если команда pop вызвана для пустой структуры
 данных, то ожидается “­1”.
 Формат выходных данных.
 Требуется напечатать YES ­ если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не
 оправдалось, то напечатать NO.
 4_2. ​Реализовать дек с динамическим зацикленным буфером.
 */

#include <iostream>
#include <string.h>

using namespace std;
#define SIZE 8

class deque {
private:
    int length, capacity, *arr;
    int head, tail;
    // функция преобразовывает отрицательные индексы
    // и возвращает правильный индекс, когда он больше чем объем дека (capacity)
    int& module(int &index)
    {
        if (index < 0)
        {
            index = capacity + index;
        }
        else index %= capacity;
        return arr[index];
    }
    
public:
    
    deque()
    {
        length = 0;
        capacity = SIZE;
        head = 0;
        tail = 0;
        arr = new int[SIZE];
    }
    
    void push_front(int data)
    {
        if (length == capacity-1)
        {
            grow();
        }
        module(tail);
        arr[tail] = data;
        tail++;
        length++;
    }
    
    void push_back(int data)
    {
        if (length == capacity-1)
        {
            grow();
        }
        --head;
        module(head);
        arr[head] = data;
        length++;
    }
    
    int pop_back() {
        if (head%capacity == tail%capacity)
            return -1;
        module(head);
        int var = arr[head];
        head++;
        length--;
        return var;
    }
    
    int pop_front() {
        if (head%capacity == tail%capacity)
            return -1;
        --tail;
        module(tail);
        int var = arr[tail];
        length--;
        return var;
    }
    
    void grow()
    {
        int *tmp = new int[capacity*2];
        int i = 0;
        int elem = 0;
        while ((elem = this->pop_back()) != -1 ){
            tmp[i] = elem;
            i++;
            length++;
        }
        delete [] arr;
        tail = i;
        head = 0;
        capacity *= 2;
        arr=tmp;
    }
    ~deque()
    {
        delete[] arr;
    }
};

int main() {
    int n = 0;
    cin >> n;
    deque first_d;
    
    int command, var;
    
    for (int i = 0 ; i < n; i++)
    {
        cin >> command >> var;
        switch (command)
        {
            case 1:
                first_d.push_front(var);
                break;
            case 2:
                if (first_d.pop_front() != var)
                {
                    cout << "NO";
                    return 0;
                }
                break;
            case 3:
                first_d.push_back(var);
                break;
            case 4:
                if (first_d.pop_back() != var)
                {
                    cout << "NO";
                    return 0;
                }
                break;
        }
    }
    cout << "YES";
    return 0;
}