
/*
 6_1. MSD для строк.
 Дан массив строк. Количество строк не больше 10 . Отсортировать массив методом поразрядной
 сортировки MSD по символам. Размер алфавита ­ 256 символов. Последний символ строки = ‘\0’.
 */

#include <iostream>
#include <vector>

using namespace std;

void msd_sort(vector <string>::iterator begin, vector <string>::iterator end, int offset)
{
    const size_t ascii = 256;
    //Каждая строка(вектора векторов) принадлежит какому-то опредленному символу.
    //В строке(вектора векторов) может находится несколько строк, если у них одинаковые символы
    //Порядок сравнение символов определяется переменной offset(насколько смещаемся по строке)
    vector<vector <string>> array(ascii);
    for (vector <string>::iterator i = begin; i != end; i++)
        //добавляем элемент *i в конец array[X], где X номер элемента Y в таблице ASCII, где Y символ строки с номером offset
        array[(int) ((*i)[offset])].push_back(*i);
    
    //Вызываем реккурсию для строк(вектора векторов) где лежит более одной строки
    //i начинается с 1, чтобы когда наступит конец строки(/0 при преобразовании типов это 0) рекурсия закончилась
    for (int i = 1; i < ascii; i++)
    {
        if (array[i].size() > 1)
            msd_sort(array[i].begin(), array[i].end(), offset + 1);
    }
    
    //Отсортированный вывод в массив
    int offset_vertical = 0;
    for (vector <string>::iterator i = begin; i != end;)
    {
        for (vector <string>::iterator j = array[offset_vertical].begin(); j != array[offset_vertical].end(); j++)
        {
            *i = *j;
            i++;
        }
            offset_vertical++;
    }
    
}

int main()
{
    vector <string> strings;
    string buffer;
    
    while (cin >> buffer)
        strings.push_back(buffer);
    
    msd_sort(strings.begin(), strings.end(), 0);
    
    for (vector <string>::iterator i = strings.begin(); i != strings.end(); i++)
        cout << *i << endl;
    
    return 0;
}

