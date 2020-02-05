#include "skiplist.hpp"
#include <pthread.h>
#define size_of_mass_1 3
#define size_of_mass_2 1
extern int MAX_LEVEL;

//создадим струткуру SkipList
SkipList<int> *skip_list = new SkipList<int>();

std::vector<Node<int>*> predecessors(MAX_LEVEL + 1);
std::vector<Node<int>*> successors(MAX_LEVEL + 1);

void* func_for_write(void* arg){
    int* mass = (int *)arg;
    for(int i = 0; i< size_of_mass_1; i++){
        skip_list->insert(mass[i]);
    }

}

void* func_for_remove(void* arg){
    int* mass = (int *)arg;
    for(int i = 0; i< size_of_mass_2; i++){
        skip_list->remove(mass[i]);
    }

}

int main() {

    pthread_t threads_1;
    pthread_t threads_2;

    int mass_of_elemnts[size_of_mass_1] = {1,2,3};
    int mass_to_remove[size_of_mass_2]= {1};

    skip_list->find(5, predecessors, successors);

    pthread_create(&threads_1, NULL, func_for_write, (void*)mass_of_elemnts);
    pthread_create(&threads_2, NULL, func_for_remove, (void*)mass_to_remove);


     for(int i = 0; i < 3; i++){
         skip_list->insert(i);
     }
     std::cout << "Before remove 1 " << std::endl;
     skip_list->print_skiplist();
     skip_list->remove(1);
     std::cout << "After remove 1 " << std::endl;

     skip_list->print_skiplist();


    return 0;
}
