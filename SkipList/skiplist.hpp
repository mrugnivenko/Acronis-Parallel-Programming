#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H
#include "atomic_markable_reference.hpp"
//#include "node.hpp"
extern int MAX_LEVEL;

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


//для след функции
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);

//функция для количества уровней нового элемента
int number_of_levels() {
    float smth_like_coin = dis(gen);
    int max_level = 0;
    while (smth_like_coin < 0.5 && max_level < MAX_LEVEL) {
        max_level += 1;
        smth_like_coin = dis(gen);
    }
    return max_level;
}

template<class T> class SkipList {
    Node<T> *head;
    Node<T> *tail;
public:
    SkipList() {
        head = new Node<T>(INT_MIN, 0);
        tail = new Node<T>(INT_MAX, 0);
        for(int i = 0; i <= MAX_LEVEL; i++) {
            head->next_node[i].set(tail, false); //по все длинне есть голова и хвост и сначала голова ссылается на хвост
        }
    }

    bool find(int n_value, std::vector<Node<T>*>& predecessors, std::vector<Node<T>*>& successors) {

        int bottom_level = 0; //ищем мы всё таки на нижнем уровне
        bool *marker = new bool;
        bool inc;

        Node<T> *predecessor = new Node<T>();
	    Node<T> *current = new Node<T>();
	    Node<T> *successor = new Node<T>();

        RETRY:
        while(true) {
            predecessor = head;
            for(int i = MAX_LEVEL; i >= bottom_level; i--) {
                current = predecessor->next_node[i].getReference();
                while(true) {
                    successor = current->next_node[i].get(marker);
                    while(marker[0]) {
                        inc = predecessor->next_node[i].cas(current, successor, false, false);
                        if (!inc) {
                            goto RETRY;
                        }
                        current = predecessor->next_node[i].getReference();
			successor = current->next_node[i].get(marker);
                    }
                    if (current->key < n_value) {
                        predecessor = current;
                        current = successor;
                    } else {
                        break;
                    }
                }
                predecessors[i] = predecessor;
                successors[i] = current;
            }
            return (current->key == n_value);
        }

    }

    bool insert(int key, T element = 0) {

        int level = number_of_levels();
        int bottom_level = 0;

        std::vector<Node<T>*> predecessors(MAX_LEVEL + 1); //для созранения позиций до и после необходимого места
        std::vector<Node<T>*> successors(MAX_LEVEL + 1); //для созранения позиций до и после

        bool found = find(key, predecessors, successors);

        while(true) {
            bool found = find(key, predecessors, successors);

            if (found) {
                return false;
            }

            Node<T> *new_node = new Node<T>(key, element, level);

            for (int i = bottom_level; i <= level; i++) {
                new_node->next_node[i].set(successors[i], false);
            }

            Node<T> *predecessor = predecessors[bottom_level];
            Node<T> *successor = successors[bottom_level];

            if (!predecessor->next_node[bottom_level].cas(successor, new_node, false, false)) {
                continue;
            }

            bool *marker = new bool;
            new_node->next_node[bottom_level].get(marker);
            for(int i = bottom_level + 1; i <= level; i++) {
                while(true) {

                    predecessor = predecessors[i];
                    successor = successors[i];

                    if (predecessor->next_node[i].cas(successor, new_node, false, false)) {
                        break;
                    }
                    find(key, predecessors, successors);
                }
            }
            return true;
        }
    }

    bool remove(T element) {
        int bottom_level = 0;

        std::vector<Node<T>*> predecessors(MAX_LEVEL + 1);
        std::vector<Node<T>*> successors(MAX_LEVEL + 1);
        Node<T>* successor = nullptr;

        while(true) {
            bool found = find(element, predecessors, successors);
            if (!found) {
                return false;
            }

            Node<T>* node_to_remove = successors[bottom_level];
            for (int i = node_to_remove->top_level; i >= bottom_level + 1; i--) {
                bool *marked = new bool(false);
                successor = node_to_remove->next_node[i].get(marked);
                while(!marked[0]) {
                    node_to_remove->next_node[i].cas(successor, successor, false, true);
                    successor = node_to_remove->next_node[i].get(marked);
                }
            }
            bool *marked = new bool(false);
            successor = node_to_remove->next_node[bottom_level].get(marked);
            while (true) {
                bool marked_it = node_to_remove->next_node[bottom_level].cas(successor, successor, false, true);
                successor = successors[bottom_level]->next_node[bottom_level].get(marked);
                if (marked_it) {
                    find(element, predecessors, successors);
                    return true;
                } else if (marked[0]) {
                    return false;
                }
            }
        }
    }

    void print_skiplist() {
        std::cout << "Skiplist's top " << std::endl;
        for (int i = MAX_LEVEL; i >= 0; i--) {
            Node<T> *temp = head->next_node[i].getReference();
            std::cout << "Level " << i << ":   head -> ";
            while(temp->next_node[i].getReference() != NULL)
            {
                std::cout << temp->key << " -> ";
                temp = temp->next_node[i].getReference();
            }
            std::cout << "tail" << std::endl;
        }
        std::cout << "Skiplist's bottom\n" << std::endl;
    }


};

#endif
