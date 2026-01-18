#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct node_s {
  void *data;
  struct node_s *prev;
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

  list = malloc(sizeof(list_t));
  if (list == NULL) {
    return NULL;
  }

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;

  return list;
}

//print function for debugging
void list_print(list_t *list) {
  if (list == NULL) {
    printf("NULL list");
    return;
  }

  printf("\nsize = %zu\n", list->size);

  node_t *cur = list->head;
  size_t index = 0;

  while (cur != NULL) {
    printf("node %zu: ", index);

    if (cur->data == NULL) {
      printf("NULL data");
      return;
    } else {
      int *p = (int *)(cur->data);
      printf("data: ");
      for (int i = 0; i < 9; i++) { //*not sure how to make it adopt the data size,
        printf("%d ", p[i]); //pointer arithmetic (for my note)
      }
    }

    printf("\n");
    cur= cur->next;
    index++;
  }
}

//3x3 matrix function for testing
node_t *matrix_3x3(int start) { 

    node_t *node = malloc(sizeof(node_t));
    node->data = malloc(sizeof(int) * 9); 

    for (size_t i = 0; i < 9; i++) {
       ((int*)(node->data))[i] = i + start;
    }
    return node;
}

void list_free(list_t *list, void (*free_data)(void *data)) {
    if (list == NULL) {
        return NULL;
    }

    list_t->head->data
    free data

    list_t -> head -> next
    free head->prev

}

int list_prepend(list_t *list, void *val) {
    if (list == NULL) {
        return 1;
    }

    node_t *newNode = malloc(sizeof(node_t));
    if (newNode == NULL) {
        return 1;
    }

    newNode->data = val;
    newNode->next = list->head;
    newNode->prev = NULL;

    if (list->size == 0) {
        list->tail = newNode;
    } else {
        list->head->prev = newNode;
    }

    list->head = newNode;
    newNode->data = val;

    list->size++;
    return 0;
}

int list_append(list_t *list, void *val) {
    if (list == NULL) {
        return 1;
    }

    node_t *newNode = malloc(sizeof(node_t));
    if (newNode == NULL) {
        return 1;
    }

    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = list->tail;
    
    if (list->size == 0) {
        list->head = newNode;
    } else {
        list->tail->next = newNode;
    }

    list->tail = newNode;
    newNode->data = val;
    
    list->size++;
    return 0;

}

int main() {

    list_t *list = list_alloc();
    node_t *node0 = matrix_3x3(1);
    node_t *node1 = matrix_3x3(2);

    for(size_t i=0; i<9; i++) {
        printf("%d. ", i[(int *)(node0->data)]);
    }

    list_prepend(list, node0->data);
    list_append(list, node1->data);

    list_print(list);

    free(node0->data);
    free(node0);
    free(node1->data);
    free(node1);
}
