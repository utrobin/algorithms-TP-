
/*
 5_2. Сортировка почти упорядоченной последовательности.
 Дана последовательность целых чисел a1...an и натуральное число k, такое что для любых i, j: если j >= i + k, то a[i] <= a[j]. Требуется отсортировать последовательность. Последовательность может быть очень длинной. Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.
 */

#include <iostream>
#include <vector>

using namespace std;

//Слияние двух отсортированных частей
void merge(int *first_part, size_t first_len, int *second_part, size_t second_len, int *common_part)
{
    int i = 0;
    int j = 0;
    
    while (i < first_len && j < second_len)
    {
        if (first_part[i] < second_part[j])
        {
            common_part[i + j] = first_part[i];
            i++;
        }
        else {
            common_part[i + j] = second_part[j];
            j++;
        }
    }
    if (i == first_len)
    {
        for (; j < second_len; j++)
        {
            common_part[i + j] = second_part[j];
        }
    }
    else if (j == second_len)
    {
        for (; i < first_len; i++)
        {
            common_part[i + j] = first_part[i];
        }
    }
}

//Основная часть сортировки слиянием
void merge_sort(int *array, int k)
{
    //Создаем временный массив
    int *temp_array = new int[k];
    //Цикл по размерам массива для слияния
    for (int i = 1; i < k; i *= 2)
    {
        //offset - переменная хранящая величину насколько надо сместиться, чтобы слиять следующие части
        int offset = 0;
        while (offset + i < k)
        {
            merge(array + offset, i, array + offset + i, min(i, k - i - offset), temp_array + offset);
            offset += i * 2;
        }
        //Копируем всё с временного массива до остатка, если он есть (0 2 3 4 | 1 6 7 8 | 5 9)
        //В данном случае остаток будет 5 9
        for (int i = 0; i < min(k, offset); i++)
        {
            array[i] = temp_array[i];
        }
    }
    delete [] temp_array;
}

void improved_sort(int *array, int k, size_t size)
{
    //Cортируем первые k элементов
    merge_sort(&array[0], k);
    
    for (int i = k; i < size; i += k)
    {
        int count_element = min(k, (int)size - i);
        //Сортируем следующие k элеметов
        merge_sort(&array[i], count_element);
        //Создаём новый временный массив в который будем сливать отсортированную новую k часть
        //c предыдущей k частью
        int *temp_array = new int[2*k];
        merge(&array[i - k], k, &array[i], count_element, temp_array);
        
        for (int j = 0; j < 2*k; j++)
        {
            array[i - k + j] = temp_array[j];
        }
        
        delete [] temp_array;
    }
}

int main()
{
    int k;
    size_t size;
    cin >> size >> k;
    
    vector <int> array;
    for (int i = 0; i < size; i++)
    {
        int element;
        cin >> element;
        array.push_back(element);
    }
    
    improved_sort(&array[0], k, size);
    
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << ' ';
    }
    return 0;
}

