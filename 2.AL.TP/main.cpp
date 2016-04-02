
/*
 2_2. Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. Вначале вводится количество вершин, затем последовательно целочисленные координаты всех вершин в порядке обхода против часовой стрелки.
 n < 1000, координаты < 10000.
 Указание. Для вычисления площади n-угольника можно посчитать сумму ориентированных площадей трапеций под каждой стороной многоугольника.
*/

#include <iostream>
#include <cassert>

using namespace std;

int main() {
    int n = 0,
    first_x=0, first_y=0,
    next_x = 0, next_y =0,
    x = 0, y = 0;
    double sum = 0;
    cin >> n;
    assert (n > 0);
    assert (n < 1000);
    cin >> first_x;
    assert (first_x < 10000);
    cin >> first_y;
    assert (first_y < 10000);
    x = first_x;
    y = first_y;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> next_x;
        assert (next_x < 10000);
        cin >> next_y;
        assert (next_y < 10000);
        sum += x * next_y - y * next_x;
        x = next_x;
        y = next_y;
    }
    sum += x * first_y - y * first_x;
    sum = sum / 2;
    if (sum < 0) sum *= -1;
    cout << sum;
    return 0;
}
