#ifndef ATOMIC_MARKABLE_REFERENCE_H
#define ATOMIC_MARKABLE_REFERENCE_H
#include <atomic>
#include <iostream>
#include <random>
#include <vector>


template<class T> struct MarkableReference {

    T* next_node; //ссылка на след
    bool ind_of_marked; //маркер удаления


    //дефолтный конструктор
    MarkableReference() {
        next_node = nullptr;
        ind_of_marked = false;
    }

    //конструктор с задаными значениями
    MarkableReference(T* node, bool mark) {
        next_node = node;
        ind_of_marked = mark;
    }


    bool operator==(const MarkableReference<T>& other) {
        return (next_node == other.next_node && ind_of_marked == other.ind_of_marked);
    }
};

template<class T> class AtomicMarkableReference {
private:
    std::atomic<MarkableReference<T>*> marked_next;
public:


    //дефолтный конструктор
    AtomicMarkableReference() {
        marked_next.store(new MarkableReference<T>(nullptr, false));
    }

    //конструктор с задаными значениями
    AtomicMarkableReference(T* next_node, bool mark) {
        marked_next.store(new MarkableReference<T>(next_node, mark));
    }


    T* getReference() {
        return marked_next.load()->next_node;
    }

    T* get(bool *mark) {
        MarkableReference<T> *temp = marked_next.load();
        *mark = temp->ind_of_marked;
        return temp->next_node;
    }


    bool cas(T* expected, T* new_value, bool expected_mark, bool new_mark) {
        MarkableReference<T> *curr = marked_next.load();
        return (expected == curr->next_node && expected_mark == curr->ind_of_marked &&
                ((new_value == curr->next_node && new_mark == curr->ind_of_marked) ||
                 marked_next.compare_exchange_strong(curr, new MarkableReference<T>(new_value, new_mark))));
    }

    void set(T* new_ref, bool new_mark) {
        MarkableReference<T> *current = marked_next.load();
        if (new_ref != current->next_node || new_mark != current->ind_of_marked) {
            marked_next.store(new MarkableReference<T>(new_ref, new_mark));
        }
    }
};

#endif
