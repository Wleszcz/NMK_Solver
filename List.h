//
// Created by wiktoer on 15.05.2022.
//

#ifndef UNTITLED3_LIST_H
#define UNTITLED3_LIST_H

#include <string>

using namespace std;
struct List_element_t;
struct Position_t;

struct Position_t{
    int x;
    int y;
};

struct List_element_t {
    Position_t position;
    List_element_t* next;
    List_element_t* previous;
};


class List {

private:
    List_element_t *head;
    List_element_t *tail;


public:

    List();

    Position_t get_element(int index);
    void addLast(Position_t move);

    int size();
    void delete_last();
    void free_memory();

};



#endif //UNTITLED3_LIST_H
