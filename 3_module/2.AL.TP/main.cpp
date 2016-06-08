
/*
 Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
 Требуется построить бинарное дерево, заданное наивным порядком вставки.
 Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
 2_4. Выведите элементы в порядке level-order (по слоям, “в ширину”).
*/

#include <iostream>
#include <queue>

using namespace std;

struct node
{
    int value;
    node *right;
    node *left;
    node (int v = 0)
    {
        value = v;
        right = NULL;
        left = NULL;
    }
};

node *insert(node *root, int value)
{
    if (root == NULL)
    {
        root = new node(value);
    }else if (value <= root->value)
    {
        root->left = insert(root->left, value);
    } else
    {
        root->right = insert(root->right, value);
    }
    return root;
}

void level_order(node* root)
{
    queue <node*> queue;
    queue.push(root);
    
    while (!queue.empty())
    {
        node* current = queue.front();
        cout << current->value << " ";
        if (current->left != NULL)
        {
            queue.push(current->left);
        }
        if (current->right != NULL)
        {
            queue.push(current->right);
        }
        queue.pop();
    }
}

void delete_tree(node *root)
{
    if (root != NULL)
    {
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}

int main()
{
    int count = 0;
    cin >> count;
    node *root = NULL;
    int value = 0;
    
    for (int i = 0; i < count; i++)
    {
        cin >> value;
        root = insert(root, value);
    }
    
    level_order(root);
    delete_tree(root);
    
    return 0;
}