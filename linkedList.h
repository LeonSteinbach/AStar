#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node;

struct node {
   int data;
   int key;
   struct node *next;
};

void printList();
void insertFirst(int key, int data);
struct node* deleteFirst();
bool isEmpty();
struct node* find(int key);
struct node* delete(int key);
void sort();
void reverse(struct node** head_ref);

#endif