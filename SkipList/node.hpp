#include "skiplist.hpp"
int MAX_LEVEL = 9;

template<class T> struct Node
{

    int top_level; //количество соответсвующих нод в структуре (итмеется ввиду в высоту)
    int key; //на самом деле реальное значение лежит тут, а не в Value тут потому, что я делеал по шаблону из книги
    std::vector<AtomicMarkableReference<Node<T>>> next_node; //указатель на следующую ноду
    T value;


    //конструктор с конкретными значениями
    Node(int node_key, T node_value, int nodes_height = MAX_LEVEL)
    {
        top_level = nodes_height;
        this->key = node_key;
        next_node = std::vector<AtomicMarkableReference<Node<T>>>(nodes_height + 1);
        this->value = node_value;
    }

    //конструктор дефолтный
    Node()
    {
        top_level = MAX_LEVEL;
        key = 0;
        next_node = std::vector<AtomicMarkableReference<Node<T>>>(MAX_LEVEL + 1);
    }

};


