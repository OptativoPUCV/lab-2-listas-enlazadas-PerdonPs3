#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List*) malloc(sizeof(List));
    if(list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    
    return list;
}

void * firstList(List * list) {
    if(list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if(list == NULL || list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if(list == NULL || list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if(list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    if(list == NULL) return;

    Node* nuevoNodo = (Node*) malloc(sizeof(Node));
    if(nuevoNodo == NULL) return;

    nuevoNodo->data = data;
    nuevoNodo->next = list->head;
    nuevoNodo->prev = NULL;
    
    if(list->head != NULL) list->head->prev = nuevoNodo;
    else list->tail = nuevoNodo;
    list->head = nuevoNodo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if(list == NULL || list->current == NULL) return;
    Node* nuevoNodo = (Node*) malloc(sizeof(Node));
    if(nuevoNodo == NULL) return;
    nuevoNodo->data = data;
    nuevoNodo->prev = list->current;
    nuevoNodo->next = list->current->next;
    if(list->current->next != NULL) list->current->next->prev = nuevoNodo;
    else list->tail = nuevoNodo;
    list->current->next = nuevoNodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list == NULL || list->current == NULL) return NULL;
    Node* eliminar = list->current;
    void* datoEliminado = eliminar->data;
    if(eliminar->prev != NULL) eliminar->prev->next = eliminar->next;
    else list->head = eliminar->next;
    if(eliminar->next != NULL) eliminar->next->prev = eliminar->prev;
    else list->tail = eliminar->prev;
    list->current = eliminar->next;
    free(eliminar);
    return datoEliminado;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}