#include <iostream>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;

class tree_node
{
public:
    int left;
    int right;
    int index;
    unsigned char symbol;
    int frequence;
    
    tree_node(char s, int i, int f = 0)
    {
        symbol = s;
        frequence = f;
        index = i;
        left = -1;
        right = -1;
    }
    
    bool is_end()
    {
        return left < 0 && right < 0;
    }
};

struct comparison
{
    bool operator()(const tree_node &l, const tree_node &r)
    const
    {
        return l.frequence > r.frequence;
    }
};

tree_node merge(tree_node left, tree_node right, int index)
{
    tree_node node(' ', index, left.frequence + right.frequence);
    node.left = left.index;
    node.right = right.index;
    return node;
}

struct code_symbol
{
    char symbol;
    vector <int> code;
    
    code_symbol(char s, vector <int> c)
    {
        symbol = s;
        code = c;
    }
    
};

void construction_table(tree_node &current_node, vector <int> &bites, vector <code_symbol> &table, vector <tree_node> &main_tree)
{
    if(current_node.is_end())
    {
        bool is_empty = false;
        if (bites.empty())
        {
            bites.push_back(0);
            is_empty = true;
        }
        
        code_symbol current_code(current_node.symbol, bites);
        table.push_back(current_code);
        if (is_empty)
        {
            is_empty = false;
            bites.pop_back();
        }
        return;
    }
    
    bites.push_back(0);
    tree_node left_node = main_tree[current_node.left];
    construction_table(left_node, bites, table, main_tree);
    bites.pop_back();
    
    bites.push_back(1);
    tree_node right_node = main_tree[current_node.right];
    construction_table(right_node, bites, table, main_tree);
    bites.pop_back();
}

class OutBitStream
{
    vector <unsigned char> buffer;
    int bits_count;
    
public:
    OutBitStream(): bits_count(0) {}
    void WriteBit (unsigned char bit)
    {
        if (bits_count >= buffer.size() * 8)
            buffer.push_back(0);
        
        if (bit != 0)
        {
            int bit_pos = (bits_count + 1) % 8;
            if (bit_pos != 0)
                bit_pos = 8 - bit_pos;
            buffer[bits_count / 8] |= 1 << bit_pos;
        }
        bits_count++;
        
    }
    
    void WriteByte (unsigned char byte)
    {
        if (bits_count % 8 == 0)
        {
            buffer.push_back(byte);
        }
        else
        {
            int offset = bits_count % 8;
            buffer[bits_count / 8] |= byte >> offset;
            buffer.push_back(0);
            buffer[bits_count / 8 + 1] |= byte << (8 - offset);
        }
        bits_count += 8;
    }
    
    const unsigned char* GetBuffer() const
    {
        return buffer.data();
    }
    
    unsigned long size() const
    {
        return buffer.size();
    }
};

void coding_tree(tree_node &current_node, vector <tree_node> &main_tree, OutBitStream &buffer)
{
    if(current_node.is_end())
    {
        buffer.WriteBit(1);
        buffer.WriteByte(current_node.symbol);
        return;
    }
    
    buffer.WriteBit(0);
    
    tree_node left_node = main_tree[current_node.left];
    coding_tree(left_node, main_tree, buffer);
    
    tree_node right_node = main_tree[current_node.right];
    coding_tree(right_node, main_tree, buffer);
}

void bits_in_the_tree(vector <tree_node> &main_tree, int &amount_bit)
{
    for (int i = 0; i < main_tree.size(); i++)
    {
        if (main_tree[i].is_end())
        {
            amount_bit = amount_bit + 9;
        }
        else
        {
            amount_bit = amount_bit + 1;
        }
    }
}

void compress_string(const string &source, string &compressed)
{
    setlocale(LC_CTYPE, "rus");
    vector <int> frequency_symbols(256, 0);
    
    for (int i = 0; i < source.length(); i++)
    {
        int value = (unsigned char)source[i];
        frequency_symbols[value]++;
    }
    
    vector <tree_node> main_tree;
    int size = 0;
    for (int i = 0; i < 256; i++)
    {
        if (frequency_symbols[i] > 0)
        {
            main_tree.push_back(tree_node(i, size, frequency_symbols[i]));
            size++;
        }
    }
    
    priority_queue <tree_node, vector <tree_node> , comparison> pq (comparison(), main_tree);
    
    while (pq.size() >= 2)
    {
        tree_node first = pq.top();
        pq.pop();
        tree_node second = pq.top();
        pq.pop();
        tree_node merged_node = merge(first, second, size);
        main_tree.push_back(merged_node);
        size++;
        pq.push(merged_node);
    }
    
    tree_node root = pq.top();
    pq.pop();
    
    vector <int> bites;
    vector <code_symbol> table;
    construction_table(root, bites, table, main_tree);
    
    OutBitStream buffer;
    coding_tree(root, main_tree, buffer);
    
    int amount_bit = 0;
    bits_in_the_tree(main_tree, amount_bit);

    vector <int> coded_symbols;
    for (int i = 0; i < source.length(); i++)
    {
        for (int j = 0; j < table.size(); j++)
        {
            if (table[j].symbol == source[i])
            {
                for (int k = 0; k < table[j].code.size(); k++)
                {
                    coded_symbols.push_back(table[j].code[k]);
                }
                break;
            }
        }
    }
    
    int amount = (int)coded_symbols.size() + amount_bit;
    int remainder = amount % 8;
    buffer.WriteByte(remainder);
    
    for (int i = 0; i < coded_symbols.size(); i++)
    {
        if (coded_symbols[i] == 0)
            buffer.WriteBit(0);
        else
            buffer.WriteBit(1);
    }
    
    for (int i = 0; i < buffer.size(); i++)
        compressed.push_back(buffer.GetBuffer()[i]);
}

class InBitStream
{
    vector <unsigned char> buffer;
    int bits_read;
    
public:
    InBitStream(const string &str): bits_read(0)
    {
        for (int i = 0; i < str.size(); i++)
            buffer.push_back((unsigned char)str[i]);
        
    }
    unsigned char ReadBit()
    {
        assert (bits_read < buffer.size() * 8);
        int offset = bits_read % 8;
        unsigned char result = buffer[bits_read / 8];
        result = result >> (7 - offset);
        result &= 1;
        bits_read++;
        return result;
    }
    
    unsigned char ReadByte()
    {
        assert (bits_read + 8 <= buffer.size() * 8);
        unsigned  char result = 0;
        if (bits_read % 8 == 0)
            result = buffer[bits_read / 8];
        else
        {
            int offset = bits_read % 8;
            result |= buffer[bits_read / 8] << offset;
            result |= buffer[bits_read / 8 + 1] >> (8 - offset);
        }
        bits_read += 8;
        return result;
    }
};

void recovery_tree(InBitStream &buffer, vector <tree_node> &main_tree, int &amount)
{
    if (buffer.ReadBit() == 1)
    {
        tree_node node(buffer.ReadByte(), amount);
        main_tree.push_back(node);
        amount = amount + 1;
        return;
    }
    
    tree_node node(' ', amount);
    node.left = amount + 1;
    main_tree.push_back(node);
    amount = amount + 1;
    
    recovery_tree(buffer, main_tree, amount);
    
    for (int i = 0; i < main_tree.size(); i++)
    {
        if (node.left == main_tree[i].left)
        {
            main_tree[i].right = amount;
            break;
        }
    }
    
    recovery_tree(buffer, main_tree, amount);
}

unsigned char decoding_tree(tree_node &current_node, InBitStream &buffer, vector <tree_node> &main_tree, int &count)
{
    if(current_node.is_end())
    {
        return current_node.symbol;
    }
    
    count++;
    
    if (buffer.ReadBit() == 0)
    {
        tree_node left_node = main_tree[current_node.left];
        return decoding_tree(left_node, buffer, main_tree, count);
    }
    else
    {
        tree_node right_node = main_tree[current_node.right];
        return decoding_tree(right_node, buffer, main_tree, count);
    }
}

void decompress_string(const string &compressed, string &result)
{
    
    setlocale(LC_CTYPE, "rus");
    InBitStream buffer(compressed);
    
    int amount = 0;
    vector <tree_node> main_tree;
    recovery_tree(buffer, main_tree, amount);
    
    int amount_bit = 0;
    bits_in_the_tree(main_tree, amount_bit);
    
    int remainder = buffer.ReadByte();
    
    int last_bit = 1;
    if (remainder == 0)
    {
        last_bit = 0;
    }
    
    int remaining_bits = ((int)compressed.size() - 1 - last_bit) * 8 + remainder - amount_bit;
    
    while (remaining_bits > 0)
    {
        int count = 0;
        
        unsigned char var = decoding_tree(main_tree[0], buffer, main_tree, count);
        result.push_back(var);
        
        //если 1 узел у дерева
        if (count == 0)
            count++;
        
        remaining_bits = remaining_bits - count;
    }
}

int main()
{
    string str1 = "ааа";
    cout << str1;
    string str2;
    compress_string(str1, str2);
}

