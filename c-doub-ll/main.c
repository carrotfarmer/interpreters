#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  char *data;
  struct Node *next;
  struct Node *prev;
};

struct LinkedList {
  struct Node *head;
  size_t size;
};

struct LinkedList init_list() {
  struct LinkedList list = {.size = 0, .head = NULL};
  return list;
}

void insert(struct LinkedList *list, char *newData) {
  if (list->size == 0) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = newData;
    newNode->next = NULL;
    newNode->prev = NULL;

    list->head = newNode;
    list->size++;
  } else {
    struct Node *curr = list->head;
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = NULL;
    newNode->prev = curr;

    list->head = newNode;
    list->size++;
  }
}

char *pop(struct LinkedList *list) {
  struct Node *prev = list->head->prev;
  char *deleted = list->head->data;
  prev->next = NULL;
  list->head = prev;

  return deleted;
}

int find(struct LinkedList *list, char *term) {
  int i = 0;
  struct Node *curr = list->head;
  while (i < list->size && curr != NULL) {
    if (strcmp(curr->data, term) == 0) {
      return 0;
    }
    i++;
  }

  return -1;
}

void print_list(struct LinkedList *list) {
  printf("%lu\n", list->size);
  int i = 0;
  struct Node *curr = list->head;
  while (i < list->size && curr != NULL) {
    printf("elem %d: %s\n", i, curr->data);
    curr = curr->prev;
    i++;
  }
}

int main(void) {
  struct LinkedList list = init_list();
  insert(&list, "Hello");
  insert(&list, "World");
  insert(&list, "Sigma");
  insert(&list, "to be deleted");

  print_list(&list);

  char *res = pop(&list);
  printf("deleting: %s\n\n", res);

  print_list(&list);

  int found = find(&list, "Sigma");
  printf("searching for %s: %d\n", "Sigma", found);

  found = find(&list, "Wutt");
  printf("searching for %s: %d\n", "Wutt", found);

  return 0;
}
