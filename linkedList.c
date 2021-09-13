#include "./linkedList.h"

struct node {
   int data;
   int key;
   struct node *next;
};

struct node *head = NULL;
struct node *currentItem = NULL;

//display the list
void printList() {
   struct node *ptr = head;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%d,%d) ",ptr->key,ptr->data);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

//insert link at the first location
void insertFirst(int key, int data) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->key = key;
   link->data = data;
	
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}

//delete first item
struct node* deleteFirst() {

   //save reference to first link
   struct node *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   return tempLink;
}

//is list empty
bool isEmpty() {
   return head == NULL;
}

int length() {
   int length = 0;
   struct node *currentItem;
	
   for(currentItem = head; currentItem != NULL; currentItem = currentItem->next) {
      length++;
   }
	
   return length;
}

//find a link with given key
struct node* find(int key) {

   //start from the first link
   struct node* currentItem = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(currentItem->key != key) {
	
      //if it is last node
      if(currentItem->next == NULL) {
         return NULL;
      } else {
         //go to next link
         currentItem = currentItem->next;
      }
   }      
	
   //if data found, return the currentItem Link
   return currentItem;
}

//delete a link with given key
struct node* delete(int key) {

   //start from the first link
   struct node* currentItem = head;
   struct node* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(currentItem->key != key) {

      //if it is last node
      if(currentItem->next == NULL) {
         return NULL;
      } else {
         //store reference to currentItem link
         previous = currentItem;
         //move to next link
         currentItem = currentItem->next;
      }
   }

   //found a match, update the link
   if(currentItem == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the currentItem link
      previous->next = currentItem->next;
   }    
	
   return currentItem;
}

void sort() {

   int i, j, k, tempKey, tempData;
   struct node *currentItem;
   struct node *next;
	
   int size = length();
   k = size ;
	
   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      currentItem = head;
      next = head->next;
		
      for ( j = 1 ; j < k ; j++ ) {   

         if ( currentItem->data > next->data ) {
            tempData = currentItem->data;
            currentItem->data = next->data;
            next->data = tempData;

            tempKey = currentItem->key;
            currentItem->key = next->key;
            next->key = tempKey;
         }
			
         currentItem = currentItem->next;
         next = next->next;
      }
   }   
}

void reverse(struct node** head_ref) {
   struct node* prev   = NULL;
   struct node* currentItem = *head_ref;
   struct node* next;
	
   while (currentItem != NULL) {
      next  = currentItem->next;
      currentItem->next = prev;   
      prev = currentItem;
      currentItem = next;
   }
	
   *head_ref = prev;
}