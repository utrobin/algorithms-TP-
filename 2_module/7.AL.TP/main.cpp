#include <iostream>
#include <stack>

struct interval
{
    int left, right;
    interval (int l, int r)
    {
        left = l;
        right = r;
    }
};

//сортировка вставками
void insert_sort(BlackInt *array, int n)
{
    BlackInt temp;
    int previous;
    for (int i = 1; i < n; i++)
    {
        temp = array[i];
        previous = i -1;
        while (previous >= 0 && array[previous] > temp)
        {
            array[previous+1] = array[previous];
            previous--;
        }
        array[previous+1] = temp;
    }
}

void sort(BlackInt *begin, BlackInt *end)
{
    std::stack <interval> stack;
    stack.push(interval(0, (int)(end - begin)));
    
    while (!stack.empty())
    {
        interval range = stack.top();
        stack.pop();
        
        if ( range.right - range.left > 258)
        {
            int random = 7;
            BlackInt temp_array[random];
            for (int i = 0; i < random; i++)
                temp_array[i] = begin[rand() % (range.right - range.left) + range.left];
            
            
            insert_sort(temp_array, random);
            
            int i = range.left;
            int j = range.right - 1;
            
            while (i <= j)
            {
                while (begin[i] < temp_array[random/2])
                {
                    i++;
                    if (i > j)
                        break;
                }
                while (begin[j] > temp_array[random/2])
                {
                    j--;
                    if (i > j)
                        break;
                }
                if (i <= j)
                {
                    std::swap(begin[i], begin[j]);
                    i++;
                    j--;
                }
            };
            
            interval s1(range.left, i);
            if (s1.left <= s1.right)
                stack.push(s1);
            interval s2(j, range.right);
            if (s2.left <= s2.right)
                stack.push(s2);
        }else
            //Cортировка Шелла
        {
            for(int d = (range.right - range.left) / 2; d != 0; d /= 2)
                for(int i = range.left + d; i < range.right; i++)
                    for(int j = i; j - range.left >= d && begin[j] < begin [j - d]; j -= d)
                        std::swap(begin[j], begin [j - d]);
        }
    }
}