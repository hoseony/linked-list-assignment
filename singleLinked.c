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



list_t *list_alloc(void) {
	list_t *list;
  list = NULL;

  list = malloc(sizeof(list_t)); // dynamically allocate
  
  if (list == NULL) { //check if allocation fails
    return NULL;
  }

  return list;
}


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


int list_insert(list_t *list, int val, size_t pos) {
  if (list == NULL) {
    return 1;
  }

  if (pos == 0) {
    return list_prepend(list, val);
  } else if (pos == list->size) {
    return list_append(list, val);
  } else if (pos > list->size) {
    return 1;
  } else {

    node_t *prev = list->head;

    for (size_t i = 0; i < pos - 1; i++) {
      prev = prev->next;
    }

    node_t *newNode = malloc(sizeof(node_t));
    if (newNode == NULL) {
      return 1;
    }

    newNode->data = val;

    newNode->next = prev->next;
    prev->next = newNode;

    list->size++;
    return 0;
  }

}

int list_rm(list_t *list, int *val, size_t pos) {
  if (list == NULL) {
    return 1;
  }

  if (pos > list->size) {
    return 1;
  }

  node_t *targetNode;
  node_t *prev;
  prev = list->head;

  if (pos == 0) {
    targetNode = list->head;
    list->head = targetNode->next; //targetNode->next should be NULL tho

    if (list->size == 1) {
      list->tail = NULL; 
    }
  } else {

    for (size_t i = 0; i < pos - 1; i++) {
      prev = prev->next;
    }

    targetNode = prev->next;
    prev->next = targetNode->next;

    if (pos == list->size-1) { //since starts from 0
      list->tail = prev;
    }
  }
  
  if (val != NULL) {
    *val = targetNode->data;
  }

  free(targetNode);
  list->size--;
  return 0;
}
  /** logic:
  if *val != NULL, val = targetNode->data

  if head (pos == 0)
   - targetNode = list->head
   - list->head = targetNode->next

  find previous node (call it prev)
   - targetNode = prev->next
   - prev->next = targetNode->next

  if targetNode is tail
   - list->tail = prev

  what if size 1? (only when pos == 0)
   - make tail to be NULL
   - 
  **/


int main(void) {
  list_t *list = list_alloc();

  list_prepend(list, 1);
  list_prepend(list, 2);
  list_prepend(list, 3);
  list_append(list, 0);

  list_print(list);

  list_insert(list, 30, 3);
  list_print(list);

  list_rm(list, NULL, 3);
  list_print(list);

  list_free(list);
}
