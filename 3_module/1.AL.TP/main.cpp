
/*
 Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв. Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
 Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
 1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
 g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct box
{
    box()
    {
        deleted = false;
    }
    string data;
    bool deleted;
};

class hash_table
{
public:
    hash_table(size_t initialSize) : table(initialSize, 0), count_keys(0) {}
    
    bool add(const string &key);
    bool remove(const string &key);
    bool find(const string &key) const;
    
    ~hash_table() { clean(); }
    
private:
    size_t count_keys;
    vector <box*> table;
    
    void refresh_hash();
    void clean();
};

const int hash_parametr = 29;
int hash_function(const string &s, size_t M)
{
    int summary = 0;
    for (int i = 0; i < s.length(); i++)
    {
        summary = (summary * hash_parametr + s[i]) % M;
    }
    
    return summary;
}

bool hash_table :: add(const string &key)
{
    if (count_keys == table.size()*3/4)
    {
        refresh_hash();
    }
    
    size_t hash = hash_function(key, table.size());
    size_t del = table.size();
    for (int i = 0; i < table.size(); i++)
    {
        hash = (hash + i) % table.size();
        
        if (table[hash] == 0)
        {
            if (del == table.size())
            {
                table[hash] = new box;
                table[hash]->data = key;
                table[hash]->deleted = false;
            }
            else
            {
                table[del]->data = key;
                table[del]->deleted = false;
            }
            
            count_keys++;
            return true;
        }
        else if (table[hash]->deleted)
        {
            if (del == table.size())
            {
                del = hash;
            }
        }
        else if (table[hash]->data == key)
        {
            return false;
        }
    }
    if (del != table.size())
    {
        table[del]->data = key;
        table[del]->deleted = false;
        count_keys++;
        return true;
    }
    return true;
}

bool hash_table :: find(const string &key)
const
{
    size_t hash = hash_function(key, table.size());
    for (int i = 0; i < table.size(); i++)
    {
        hash = ( hash + i ) % table.size();
        
        if ( table[hash] == 0 )
        {
            return false;
        }
        else if ( table[hash]->data == key )
        {
            return true;
        }
    }
    return false;
}

bool hash_table :: remove(const string &key)
{
    size_t hash = hash_function(key, table.size());
    for (int i = 0; i < table.size(); i++)
    {
        hash = ( hash + i ) % table.size();
        
        if (table[hash] == 0)
        {
            return false;
        }
        else if ( table[hash]->data == key )
        {
            table[hash]->data = "";
            table[hash]->deleted = true;
            count_keys--;
            return true;
        }
    }
    
    return false;
}

void hash_table :: refresh_hash()
{
    const size_t new_size = table.size() * 2;
    vector <box*> newTable(new_size, 0);
    
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i] == 0 || table[i]->deleted)
        {
            continue;
        }
        
        size_t newHash = hash_function(table[i]->data, new_size);
        for (int j = 0; j < table.size(); j++)
        {
            newHash = (newHash + j ) % new_size;
            
            if (newTable[newHash] == 0)
            {
                newTable[newHash] = table[i];
                break;
            }
        }
    }
    swap(table, newTable);
}

void hash_table :: clean()
{
    for (int i = 0; i < table.size(); i++)
    {
        if ( table[i] != 0 )
        {
            delete table[i];
        }
    }
}

int main()
{
    hash_table stringsTable(8);
    
    while (true)
    {
        string s;
        cin >> s;
        if (cin.eof())
        {
            break;
        }
        
        if (s == "+")
        {
            cin >> s;
            cout << (stringsTable.add( s ) ? "OK" : "FAIL") << endl;
        }else if (s == "-")
        {
            cin >> s;
            cout << (stringsTable.remove( s ) ? "OK" : "FAIL") << endl;
        }else if (s == "?")
        {
            cin >> s;
            cout << (stringsTable.find( s ) ? "OK" : "FAIL") << endl;
        }
    }
    
    return 0;
}