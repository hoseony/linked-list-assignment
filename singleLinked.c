#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
	int data;
	struct node_s *next;
} node_t;

typedef struct list_s {
	node_t *head;
	node_t *tail;
	size_t size;
} list_t;


// functions to implement

list_t *list_alloc(void) {
	list_t *list;
  list = NULL;

  list = malloc(sizeof(list_t)); // dynamically allocate
  
  if (list == NULL) { //check if allocation fails
    return NULL;
  }

  return list;
}

/** test code for list_alloc()

int main(void) {
  list_t *list = list_alloc();

  if (!list) {
    printf("list_alloc failed");
    return 1;
  }

  printf("pointer %p\n", (void *)list);
  printf("list->head %p\n", (void *)list->head);
  printf("list->tail %p\n", (void *)list->tail);
  printf("list->size %zu\n", list->size);
  
  free(list);

  return 0;
}
**/

void list_free(list_t *list) {

  if (list == NULL) {
    return;
  }

  node_t *ptr;
  ptr = list->head;

  while (ptr != NULL) {
    node_t *next = ptr->next;
    free(ptr);
    ptr = next;
  }

  free(list);
}

/** test code fzor list_free with dummy data

int main(void) {
  list_t *list = list_alloc();

  node_t *a = malloc(sizeof(node_t));
  node_t *b = malloc(sizeof(node_t));
  node_t *c = malloc(sizeof(node_t));

  a->data = 10;
  b->data = 20;
  c->data = 30;

  a->next = b;
  b->next = c;
  c->next = NULL;

  list->head = a;
  list->tail = c;
  list->size = 3;

  printf("pointer %p\n", (void *)list->head);
  printf("pointer %p\n", (void *)list->tail);
  printf("pointer %p\n", (void *)list->size);

  list_free(list);
} //tested with leaks --atExist -- ./singleLinked, 0 leaks

**/

int list_prepend(list_t *list, int val) {

  if (list == NULL) {
    return 1;
  }

  node_t *newNode = malloc(sizeof(node_t));
  if (newNode == NULL) { //check for allocation failure
    return 1;
  } 
  
  newNode->data = val;          //insert data
  newNode->next = list->head;   //newNode points to the head of the original pointer (putting newNode before)
  list->head = newNode;         //point head to new node

  if(list->size == 0) { //check case of size 0
    list->tail = newNode;
  }

  list->size++;
  return 0;
}

int list_append(list_t *list, int val) {

  if (list == NULL) {
    return 1;
  }

  node_t *newNode = malloc(sizeof(node_t));
  if (newNode == NULL) {
    return 1;
  }

  newNode->data = val;
  newNode->next = NULL;
  
  if(list->size == 0) {
    list->head = newNode;
    list->tail = newNode;
  } else {
    list->tail->next = newNode;
    list->tail = newNode;
  }

  list->size++;
  return 0;
}




//made for debugging purpose
void list_print(list_t *list) {
  if (list == NULL) {
    printf("NULL list");
    return;
  }

  printf("list: head=%p, tail=%p, size =%zu \n", (void *)list->head, (void *)list->tail, list->size);

  printf("head ->");
  node_t *ptr = list->head;

  while (ptr != NULL) {
    printf("(%p)[%d]", (void *)ptr, ptr->data);
    ptr = ptr->next;
  }

  printf("\n tail check, tail: (%p)[%d], tail->next=(%p\n)", (void *)list->tail, list->tail->data, (void *)list->tail->next); //to check tail node
}


/**

//testing code for list_prepend
int main(void) {
  list_t *list = list_alloc();

  printf("pointer %p\n", (void *)list->head);
  printf("pointer %p\n", (void *)list->tail);
  printf("pointer %p\n", (void *)list->size);

  list_prepend(list, 10);

  printf("pointer %p\n", (void *)list->head);
  printf("pointer %p\n", (void *)list->tail);
  printf("pointer %p\n", (void *)list->size);
  printf("data %d\n", list->head->data);
  printf("next %p\n", (void *)list->head->next);

  list_free(list);
}

**/

int main(void) {
  list_t *list = list_alloc();

  list_prepend(list, 1);
  list_prepend(list, 2);
  list_prepend(list, 3);
  list_append(list, 4);

  list_print(list);
  list_free(list);
}
