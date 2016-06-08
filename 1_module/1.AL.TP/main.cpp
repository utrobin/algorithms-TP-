
/*
1_5. Вывести квадраты натуральных чисел от 1 до n, используя только O(n) операций сложения и вычитания (умножением пользоваться нельзя).
n ≤ 1000.
*/

#include <iostream>

using namespace std;
void step(ostream& out, int n)
{
    unsigned int rez = 1;
    unsigned int x = 1;
    while(x <= n)
    {
        out << rez << " ";
        rez += x + x + 1;
        x++;
    }
    
}

int main()
{
    int n;
    std::cin >> n;
    step(cout, n);
    return 0;
}