//
// Created by wikto on 15.05.2022.
//
using namespace std;
#include "List.h"

List::List() {
    head = new List_element_t;
    tail = new List_element_t;
    head = NULL;
    tail = NULL;
};


void List::addLast(Position_t position) {
    if (head == NULL) {
        head = new List_element_t;
        (head)->position=position;
        (head)->next = NULL;
        (head)->previous = NULL;
        tail = head;

    }
    else {
        List_element_t* element = tail;

        element->next = new List_element_t;
        element->next->position=position;
        element->next->next = NULL;
        element->next->previous = element;
        tail = element->next;
    }
}

void List::delete_last() {
    if (head->next == NULL) {
        head = NULL;
        tail = NULL;
    }
    else {
        List_element_t* element =  ( tail->previous);

       // cout << element->next->key << endl;
        free(element->next);
        element->next = NULL;
        tail = element;
    }
}

Position_t List::get_element(int number) {
    List_element_t* element = head;
    int count = 0;
    while (element != NULL) {
        if (count == number) {
            return element->position;

        }
        count++;
        element = element->next;
    }
    Position_t error{};
    error.x=-1;
    error.y=-1;
    return error;
}

void List::free_memory() {
        List_element_t* tmp;


        while (head!= NULL)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }

}

int List::size(){
    List_element_t* element = head;
    int count = 0;
    while (element != NULL) {
        count++;
        element=element->next;
    }
    return count;
}







