#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

//leaks --atExit -- ./doubleLinked 

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
      for (int i = 0; i < 9; i++) { //only works for this case
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

void list_free(list_t *list, void (*free_data)(void*)) {
    if (list == NULL) {
        return;
    }

    node_t *cur = list->head;

    while (cur->next != NULL) {
        cur = cur->next;
        (*free_data)(cur->prev->data);
        free(cur->prev);
    }
    
    (*free_data)(cur->data);
    free(cur);
    free(list);
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

int list_insert(list_t *list, void *val, size_t pos) {
    if (list == NULL) {
        return 1;
    }

    node_t *newNode = malloc(sizeof(node_t));
    if (newNode == NULL) {
        return 1;
    }
    
    if (pos == 0) {
        list_append(list, val);
    }

    if (pos == list->size) {
        list_append(list, val);
    }

    newNode->data = val;
    node_t *cur;

    if (pos < ((list->size)/2)) { //use nexta
        cur = list->head;
        for(size_t i = 0; i < pos; i ++) {
            cur = cur->next;
        }
    } else { //prev
        cur = list->tail;
        for(size_t i = 0; i < (list->size)-pos; i++) {
            cur = cur->prev;
        }
    }

    newNode->next = cur;
    newNode->prev = cur->prev;

    cur->prev->next = newNode;
    cur->prev = newNode;

    list->size++;
    return 0;
}

int list_rm(list_t *list, void **val, size_t pos) {
    if (list == NULL) {
        return 1;
    }


}



//test code
int main() {
    list_t *list = list_alloc();
    node_t *node0 = matrix_3x3(1);
    node_t *node1 = matrix_3x3(2);
    node_t *node2 = matrix_3x3(3);
    node_t *node3 = matrix_3x3(4);
    node_t *node4 = matrix_3x3(5);

    for(size_t i=0; i<9; i++) {
        printf("%d. ", i[(int *)(node0->data)]);
    }

    list_prepend(list, node0->data);
    list_append(list, node1->data);
    list_append(list, node2->data);
    list_append(list, node3->data);

    list_insert(list, node4->data, 1);

    list_print(list);

    list_free(list, (void (*)(void*))free);

    free(node0); //i don't feel like this is a good way of doing thing because now I need to free this nodes again...
    free(node1);
    free(node2);
    free(node3);
    free(node4);
}
