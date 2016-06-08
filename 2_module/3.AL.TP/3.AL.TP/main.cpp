
/*
 3_2. Современники.
 Группа людей называется современниками если был такой момент, когда они могли собраться вместе. Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не исполниться 80 лет.
 Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников. В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
 Замечание. Человек мог не дожить до 18­летия, либо умереть в день 18­летия. В этих случаях принимать участие в собраниях он не мог.
 */

#include <iostream>
#include <vector>

using namespace std;

struct date
{
    int day, month, year;
    
    date (int d = 0, int m = 0, int y = 0)
    {
        day = d;
        month = m;
        year = y;
    }
    
    bool operator < (date &second)
    {
        return year < second.year ||
            (year == second.year && ( month < second.month ||
                                     ( month == second.month && day < second.day )));
    }
    
    bool operator == (date &second)
    {
        return day == second.day && month == second.month && year == second.year;
    }
    
    bool operator != (date &second)
    {
        return !(*this == second);
    }
};

//Дата активности или неактивности
struct attribute
{
    date date_at;
    bool active;
    
    attribute (struct date attribute_date = 0, bool attribute_active = true)
    {
        date_at = attribute_date;
        active = attribute_active;
    }
   
    bool operator < (attribute &second)
    {
       return date_at < second.date_at;
    }
};



class people
{
    date born, death;
    attribute p_active, p_inactive;
    bool at_active;
    
    
public:
    people (date p_born, date p_death)
    {
        born = p_born;
        death = p_death;
        at_active = false;
        
        if (death.year > born.year + 18 ||
            ( death.year == born.year + 18 && ( death.month > born.month ||
                                               ( death.month == born.month && death.day > born.day ))))
        {
            at_active = true;
            p_active = attribute(date (born.day, born.month, born.year + 18));
            if (death.year > born.year + 80 ||
                (death.year == born.year + 80 && (death.month > born.month ||
                                                  (death.month == born.month && death.day > born.day))))
                p_inactive = attribute(date (born.day, born.month, born.year + 80), false);
            else
                p_inactive = attribute(date (death.day, death.month, death.year), false);
        }
    }
    
    bool get_at_active ()
    const
    {
        return at_active;
    }
    
    attribute get_start_active ()
    const
    {
        return p_active;
    }
    
    attribute get_stop_active ()
    const
    {
        return p_inactive;
    }
};

void heap_fix(vector <attribute> &array, int n, int p)
{
    attribute temp = array[p];
    while (p < n / 2)
    {
        int child_p = 2 * p + 1;
        if (child_p < n)
        {
            if (child_p + 1 < n && array[child_p] < array[child_p + 1])
                child_p++;
            if (array[p] < array[child_p])
            {
                swap(array[p], array[child_p]);
                p = child_p;
            }
            else
                break;
        }
        else
            break;
    }
    array[p] = temp;
}

void local_heap_sort (vector <attribute> &array)
{
    for (int i = (int) array.size() / 2 - 1; i >= 0; i--)
    {
        heap_fix(array, (int) array.size(), i);
    }
    for (int i = (int) array.size() - 1; i > 0; i--)
    {
        swap(array[i], array[0]);
        heap_fix(array, i, 0);
    }
}

int solve (vector <attribute> &array)
{
    int max = 1;
    int count = 0;
    for (int i = 0; i < array.size(); i++)
    {
        array[i].active ? count++ : count --;
        if (count > max)
            max = count;
    }
    return max;
}

int main()
{
    int n = 0;
    cin >> n;
    
    vector <people> array;
    array.reserve(n);
    
    vector <attribute> times;
    int b_d = 0, b_m = 0, b_y = 0,
        d_d = 0, d_m = 0, d_y = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> b_d >> b_m >> b_y;
        cin >> d_d >> d_m >> d_y;
        
        people h(date (b_d, b_m, b_y), date (d_d, d_m, d_y));
        array.push_back(h);
        
        if (array[i].get_at_active())
        {
            times.push_back(array[i].get_start_active());
            times.push_back(array[i].get_stop_active());
        }
    }
    
    // Сортируем времена активности людей
    local_heap_sort(times);
    
    cout << solve(times);
    
    return 0;
}





