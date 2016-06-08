
/*
 2_3. Тупики.
 На вокзале есть некоторое количество тупиков, куда прибывают электрички. Этот вокзал является их конечной станцией. Дано расписание движения электричек, в котором для каждой электрички указано время ее прибытия, а также время отправления в следующий рейс. Электрички в расписании упорядочены по времени прибытия. Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером. При этом если электричка из какого­то тупика отправилась в момент времени X, то электричку, которая прибывает в момент времени X, в этот тупик ставить нельзя, а электричку, прибывающую в момент X+1 — можно.
 В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
 Напишите программу, которая по данному расписанию определяет, какое минимальное количество тупиков требуется для работы вокзала.
 Формат входных данных. Вначале вводится n ­ количество электричек в расписании. Затем вводится n строк для каждой электрички, в строке ­ время прибытия и время отправления. Время ­ натуральное число от 0 до 10^9. Строки в расписании упорядочены по времени прибытия.
 Формат выходных данных. Натуральное число ­ минимальное количеством тупиков. Максимальное время: 50мс, память: 5Мб.
 */

#include <iostream>

using namespace std;

class Heap
{
public:
    
    Heap()
    {
        array = new int[capacity];
    }
    
    const int next() { return array[0]; }
    
    const bool empty() { return size == 0; }
    
    const int get_size() { return size; }
    
    void insert(int element)
    {
        if (size == capacity)
            incruasse();
        array[size] = element;
        shift_up(size);
        size++;
    }
    
    void extract_min()
    {
        array[0] = array[size - 1];
        size--;
        sift_down(0);
    }
    
    ~Heap()
    {
        delete[] array;
    }
    
    
private:
    int* array;
    int size = 0;
    int capacity = 2;
    
    void sift_down(int index)
    {
        int left_part = 2 * index + 1;
        int right_part = 2 * index + 2;
        
        int less_part = index;
        
        if ( left_part < size && array[left_part] < array[index] )
            less_part = left_part;
        
        if ( right_part < size && array[right_part] < array[less_part] )
            less_part = right_part;
        
        if ( less_part != index )
        {
            swap(array[index], array[less_part]);
            sift_down(less_part);
        }
    }
    
    void shift_up(int index)
    {
        while ( index > 0 )
        {
            int parent = ( index - 1 ) / 2;
            
            if ( array[index] >= array[parent] )
                return;
            
            swap(array[index], array[parent]);
            
            index = parent;
        }
    }
    
    void incruasse()
    {
        int new_capacity = capacity * 2;
        int* new_array = new int[new_capacity];
        
        for ( int i = 0; i < capacity; i++ )
            new_array[i] = array[i];
        
        delete[] array;
        
        array = new_array;
        capacity = new_capacity;
    }
};


int solve(int n)
{
    int min_stubs = 0;
    int arrival, departure;
    Heap heap;
    
    for ( int i = 0; i < n; i++ )
    {
        cin >> arrival >> departure;
        
        if ( !heap.empty() )
        {
            // Если некоторые электрички к моменту прибытия уехали, извлекаем их
            while ( arrival > heap.next() && !heap.empty() )
                heap.extract_min();
        }
        
        heap.insert(departure);
        
        if ( heap.get_size() > min_stubs )
            min_stubs = heap.get_size();
    }
    
    return min_stubs;
}

int main()
{
    int n;
    cin >> n;
    
    int min_stubs = solve(n);
    cout << min_stubs;
    
    return 0;
}



