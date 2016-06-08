/*
 Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков
 пирамиду.
 Формат входных данных:
 На вход подается количество кубиков N.
 Формат выходных данных:
 Вывести число различных пирамид из N кубиков.
 6_2. Широкая пирамида. Каждый вышележащий слой пирамиды должен быть строго меньше
 нижележащего.
 */

#include <iostream>

using namespace std;

unsigned long long count(int N){
    
    if ( N <= 2){
        return 1;
    }
    long long **array = new long long* [N];
    unsigned long long result = 0;
    for (int i = 0; i < N ; i++)
    {
        array[i] = new long long[N];
    }
    for (int n = 0; n < N ; n++)
    {
        for (int m = 0; m < N ; m++)
        {
            array[n][m] = 0;
        }
    }
    array[0][0] = 1;
    array[1][1] = 1;
    int buffer = 0;
    if (N > 2)
    {
        for (int i = 2; i < N; i++)
        {
            array[i][i] = 1;
            for (int j = i - 1; j >= 0 ; j--)
            {
                buffer = i - j - 1;
                if (buffer < i / 2)
                {
                    for (int k = 0; k <= buffer ; ++k)
                    {
                        array[i][j] += array[buffer][k];
                    }
                } else
                {
                    for (int s = 0; s < j; s++)
                    {
                        array[i][j] += array[buffer][s];
                    }
                }
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        result += array[N - 1][i];
    }
    for (int i = 0; i < N; i++)
    {
        delete [] array[i];
    }
    delete [] array;
    return result;
}

int main() {
    int N;
    cin >> N;
    if (N <= 0)
    {
        cout << "ERROR";
        return 0;
    }
    cout << count(N);
    return 0;
}