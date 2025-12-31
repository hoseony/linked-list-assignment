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


//test code for list_free with dummy data
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
} //tested with leaks --atExist -- ./singleLinked
