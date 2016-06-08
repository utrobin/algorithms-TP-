
/*
 Дано число N < 106 и последовательность пар целых чисел из [-231..231] длиной N.
 Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
 Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
 Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
 При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.
 
 Построить также наивное дерево поиска по ключам Xi методом из задачи 2.

 3_2. Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска. Вывести их разницу. Разница может быть отрицательна.
*/
#include <iostream>
#include <queue>

using namespace std;

template <class T>
class tree
{
public:
    T data;
    int priority;
    tree <T> *left;
    tree <T> *right;
    
    tree(const T &d, int p = 0)
    {
        data = d;
        priority = p;
        left = NULL;
        right = NULL;
    }
};

template <class T>
class cartesian_tree
{
private:
    tree <T> *root;
public:
    cartesian_tree()
    {
        root = NULL;
    }
    
    ~cartesian_tree()
    {
        queue <tree<T> *> que;
        if(root != NULL)
        {
            que.push(root);
        }
        
        while(!que.empty())
        {
            tree <T> *c = que.front();
            if(c->left != NULL)
            {
                que.push(c->left);
            }
            if(c->right != NULL)
            {
                que.push(c->right);
            }
            
            delete c;
            que.pop();
        }
    }
    
    void split(tree <T> *c_node, const T &data, tree <T> *&left, tree <T> *&right)
    {
        if(c_node == NULL)
        {
            left = NULL;
            right = NULL;
        }
        else if(c_node->data <= data)
        {
            split(c_node->right, data, c_node->right, right);
            left = c_node;
        }
        else
        {
            split(c_node->left, data, left, c_node->left);
            right = c_node;
        }
    }
    
    void set_root(tree<T> *_root)
    {
        root = _root;
    }
    
    void add(const T &data, int priority)
    {
        tree<T> *node = new tree<T>(data, priority),
        *c_node = root,
        *prevNode = root;
        
        if(c_node == NULL) {
            set_root(node);
            return;
        }
        
        while(c_node != NULL && priority <= c_node->priority)
        {
            prevNode = c_node;
            if(data <= c_node->data)
            {
                c_node = c_node->left;
            }
            else
            {
                c_node = c_node->right;
            }
        }
        
        split(c_node, data, node->left, node->right);
        
        if(c_node == root)
        {
            root = node;
        }
        else if(data <= prevNode->data)
        {
            prevNode->left = node;
        }
        else
        {
            prevNode->right = node;
        }
    }
    
    int calc_width()
    {
        int max_width = 0,
        c_width = 0;
        
        queue<tree <T> *> layer_nodes;
        tree <T> *c = NULL;
        layer_nodes.push(root);
        
        while(!layer_nodes.empty())
        {
            if((c_width = (int)layer_nodes.size()) > max_width)
            {
                max_width = c_width;
            }
            
            for(size_t i = 0; i < c_width; i++)
            {
                c = layer_nodes.front();
                if(c->left != NULL)
                {
                    layer_nodes.push(c->left);
                }
                if(c->right != NULL)
                {
                    layer_nodes.push(c->right);
                }
                layer_nodes.pop();
            }
        }
        
        return max_width;
    }
};

template <class T>
class naive_tree
{
private:
    tree <T> *root;
public:
    naive_tree()
    {
        root = NULL;
    }
    
    ~naive_tree()
    {
        queue <tree<T> *> que;
        if(root != NULL)
        {
            que.push(root);
        }
        
        while(!que.empty())
        {
            tree <T> *c = que.front();
            if(c->left != NULL)
            {
                que.push(c->left);
            }
            if(c->right != NULL)
            {
                que.push(c->right);
            }
            
            delete c;
            que.pop();
        }
    }
    
    void set_root(tree <T> *r)
    {
        root = r;
    }
    
    void add(const T &data)
    {
        tree <T> *node = new tree<T>(data),
        *c_node = root;
        
        if(c_node == NULL)
        {
            set_root(node);
            return;
        }
        
        while(true)
        {
            if(data < c_node->data)
            {
                if(c_node->left != NULL)
                {
                    c_node = c_node->left;
                }
                else
                {
                    c_node->left = node;
                    return;
                }
            }
            else
            {
                if(c_node->right != NULL)
                {
                    c_node = c_node->right;
                }
                else
                {
                    c_node->right = node;
                    return;
                }
            }
        }
    }
    
    int calc_width()
    {
        int max_width = 0,
            c_width = 0;
        
        queue <tree<T> *> layer_nodes;
        tree <T> *c = NULL;
        layer_nodes.push(root);
        
        while(!layer_nodes.empty())
        {
            if((c_width = (int)layer_nodes.size()) > max_width)
            {
                max_width = c_width;
            }
            
            for(size_t i = 0; i < c_width; i++)
            {
                c = layer_nodes.front();
                if(c->left != NULL)
                {
                    layer_nodes.push(c->left);
                }
                if(c->right != NULL)
                {
                    layer_nodes.push(c->right);
                }
                layer_nodes.pop();
            }
        }
        
        return max_width;
    }
};

int main()
{
    naive_tree <int> naive;
    cartesian_tree <int> treap;
    
    int n = 0;
    cin >> n;
    
    int data = 0;
    int priority = 0;
    
    for(int i = 0; i < n; i++)
    {
        if(cin >> data >> priority)
        {
            naive.add(data);
            treap.add(data, priority);
        }
    }
    
    cout << (treap.calc_width() - naive.calc_width());
    
    return 0;
}